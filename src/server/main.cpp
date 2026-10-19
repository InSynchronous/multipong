#include "GameServer.h"

#include "../shared/Packet.h"

#include <algorithm>
#include <array>
#include <cerrno>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <thread>

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using Clock = std::chrono::steady_clock;

constexpr int PORT = 8080;
constexpr float TICK_RATE = 1.0f / 60.0f;

constexpr uint8_t INPUT_P1 = 1u << 0;
constexpr uint8_t INPUT_P2 = 1u << 1;

struct Client {
    int fd = -1;
    uint8_t input = 0;

    uint8_t pending[sizeof(ClientTelemetry)]{};
    size_t pending_size = 0;
};

bool send_all(int fd, const void *data, size_t size) {
    const auto *bytes = static_cast<const char *>(data);
    size_t sent = 0;

    while (sent < size) {
        ssize_t n = send(fd, bytes + sent, size - sent, MSG_NOSIGNAL);

        if (n < 0 && errno == EINTR) {
            continue;
        }

        if (n <= 0) {
            return false;
        }

        sent += static_cast<size_t>(n);
    }

    return true;
}

void disconnect_client(Client &client) {
    if (client.fd >= 0) {
        close(client.fd);
    }

    client = {};
    client.fd = -1;
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0) {
        throw std::runtime_error("socket failed");
    }

    int reuse = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, reinterpret_cast<sockaddr *>(&server_addr),
             sizeof(server_addr)) < 0) {
        close(server_fd);
        throw std::runtime_error("bind failed");
    }

    if (listen(server_fd, 5) < 0) {
        close(server_fd);
        throw std::runtime_error("listen failed");
    }

    fcntl(server_fd, F_SETFL, fcntl(server_fd, F_GETFL, 0) | O_NONBLOCK);

    std::array<Client, 2> clients{};
    GameServer game;

    auto previous = Clock::now();
    auto next_tick = previous;

    std::cout << "Listening on port " << PORT << '\n';

    while (true) {
        // accept new clients
        while (true) {
            int fd = accept(server_fd, nullptr, nullptr);

            if (fd < 0) {
                if (errno == EINTR) {
                    continue;
                }
                break;
            }

            int slot = -1;

            for (int i = 0; i < 2; ++i) {
                if (clients[i].fd < 0) {
                    slot = i;
                    break;
                }
            }

            if (slot < 0) {
                close(fd);
                continue;
            }

            int flags = fcntl(fd, F_GETFL, 0);
            if (flags >= 0) {
                fcntl(fd, F_SETFL, flags | O_NONBLOCK);
            }

            clients[slot] = {};
            clients[slot].fd = fd;

            std::cout << "Client connected in slot " << slot + 1 << '\n';
        }

        for (auto &client : clients) {
            if (client.fd < 0) {
                continue;
            }

            uint8_t buffer[128];

            while (true) {
                ssize_t n = recv(client.fd, buffer, sizeof(buffer), 0);

                if (n > 0) {
                    for (ssize_t i = 0; i < n; ++i) {
                        client.pending[client.pending_size++] = buffer[i];

                        if (client.pending_size == sizeof(ClientTelemetry)) {
                            ClientTelemetry telemetry{};
                            std::memcpy(&telemetry, client.pending,
                                        sizeof(telemetry));

                            client.input = telemetry.data;
                            client.pending_size = 0;
                        }
                    }

                    continue;
                }

                if (n == 0) {
                    std::cout << "Client disconnected\n";
                    disconnect_client(client);
                } else if (errno != EAGAIN && errno != EWOULDBLOCK &&
                           errno != EINTR) {
                    std::cout << "Client connection error\n";
                    disconnect_client(client);
                }

                break;
            }
        }

        auto now = Clock::now();

        if (now >= next_tick) {
            float dt = std::chrono::duration<float>(now - previous).count();
            previous = now;
            dt = std::min(dt, 0.05f);

            uint8_t p1_input = 0;
            uint8_t p2_input = 0;

            for (const auto &client : clients) {
                if (client.fd < 0) {
                    continue;
                }

                if (client.input & INPUT_P1) {
                    p1_input = client.input;
                } else if (client.input & INPUT_P2) {
                    p2_input = client.input;
                }
            }

            game.tick(p1_input, p2_input, dt);

            ServerTelemetry response = game.get_telemetry();

            for (auto &client : clients) {
                if (client.fd >= 0 &&
                    !send_all(client.fd, &response, sizeof(response))) {
                    std::cout
                        << "Failed to send telemetry; disconnecting client\n";
                    disconnect_client(client);
                }
            }

            next_tick = now + std::chrono::duration_cast<Clock::duration>(
                                  std::chrono::duration<float>(TICK_RATE));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    close(server_fd);
    return 0;
}
