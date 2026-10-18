
#include "Client.h"

#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

Client::Client(const char *hostname, int ip) {
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd < 0) {
        throw std::runtime_error("Failed to create socket");
    }

    addrinfo hints{};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    addrinfo *result = nullptr;
    if (getaddrinfo(hostname, nullptr, &hints, &result) != 0) {
        close(socket_fd);
        throw std::runtime_error("Failed to resolve hostname");
    }

    bool connected = false;

    for (addrinfo *entry = result; entry != nullptr; entry = entry->ai_next) {
        if (entry->ai_family == AF_INET) {
            sockaddr_in addr = *reinterpret_cast<sockaddr_in *>(entry->ai_addr);
            addr.sin_port = htons(ip);

            if (connect(socket_fd, reinterpret_cast<sockaddr *>(&addr),
                        sizeof(addr)) == 0) {
                connected = true;
                break;
            }
        }
    }

    freeaddrinfo(result);

    if (!connected) {
        close(socket_fd);
        throw std::runtime_error("Failed to connect to server");
    }
}

Client::~Client() { close(socket_fd); }

ServerTelemetry Client::sendClientTelemetry(State user, bool w, bool a, bool s,
                                            bool d, bool blocking) {
    ClientTelemetry telemetry{};

    uint8_t offset = static_cast<int>(user) == 1 ? 0 : 4;

    telemetry.data = (w << offset) | (a << (offset + 1)) | (s << (offset + 2)) |
                     (d << (offset + 3)) | (blocking << 7);

    ssize_t sent = 0;
    while (sent < sizeof(telemetry)) {
        ssize_t n =
            send(socket_fd, reinterpret_cast<const char *>(&telemetry) + sent,
                 sizeof(telemetry) - sent, 0);

        if (n <= 0) {
            throw std::runtime_error("Failed to send telemetry");
        }

        sent += n;
    }

    ServerTelemetry response{};
    ssize_t received = 0;

    while (received < sizeof(response)) {
        ssize_t n =
            recv(socket_fd, reinterpret_cast<char *>(&response) + received,
                 sizeof(response) - received, 0);

        if (n <= 0) {
            throw std::runtime_error("Failed to receive server telemetry");
        }

        received += n;
    }

    return response;
}
