#include "../shared/Packet.h"
#include <bitset>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    std::memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
        0) {
        close(server_fd);
        throw std::runtime_error("bind failed");
        return 1;
    }

    if (listen(server_fd, 5) < 0) {
        close(server_fd);
        throw std::runtime_error("listening failed");
        return 1;
    }

    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);
        std::cout << "hi" << std::endl;

        if (client_fd < 0) {
            continue;
        }

        char buffer[1024];
        ssize_t bytes_read;

        ClientTelemetry telemetry;

        while ((bytes_read = recv(client_fd, &telemetry, sizeof(telemetry),
                                  MSG_WAITALL)) == sizeof(telemetry)) {
            std::cout << "telemetry: ";
            std::cout << std::bitset<8>(telemetry.data) << std::endl;
            ServerTelemetry response = {
                640.0f,  360.0f, // Ball
                600.0f,  260.0f, // P1
                1130.0f, 260.0f  // P2
            };

            ssize_t total_sent = 0;

            while (total_sent < sizeof(response)) {
                ssize_t bytes_sent = send(
                    client_fd, reinterpret_cast<char *>(&response) + total_sent,
                    sizeof(response) - total_sent, 0);

                if (bytes_sent <= 0) {
                    break;
                }

                total_sent += bytes_sent;
            }

            if (total_sent < sizeof(response)) {
                break;
            }
        }

        close(client_fd);
    }

    close(server_fd);
    return 0;
}
