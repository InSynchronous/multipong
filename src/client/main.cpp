#include "Client.h"
#include "Game.h"
#include "Renderer.h"
#include <iostream>
#include <string>

extern const float paddle_width = 50;
extern const float paddle_height = 50;
extern State active = State::left;

void user_renderer(Renderer &r);

Renderer r(1280, 720, user_renderer);
Game *game = nullptr;

void user_renderer(Renderer &r) { if (game) game->tick(); }

int main(int argc, char *argv[]) {
    std::string server = "localhost:8080"; // default server

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "--server" && i + 1 < argc) {
            server = argv[++i];
        } else if (arg == "right") {
            // default left
            active = State::right;
        }
    }

    size_t separator = server.find(':');
    if (separator == std::string::npos) {
        std::cout << "Bad Server! Should be something like server.com:8080\n";
        return 1;
    }

    std::string host = server.substr(0, separator);
    int port;

    try {
        port = std::stoi(server.substr(separator + 1));
    } catch (...) {
        std::cout << "Bad Server! Should be something like server.com:8080\n";
        return 1;
    }

    Client client(host.c_str(), port);
    Game g(r, client);
    game = &g;

    const bool &running = r.get_status();
    while (running) {
        r.cycle_render();
    }

    return 0;
}
