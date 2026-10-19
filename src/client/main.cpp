#include "Client.h"
#include "Game.h"
#include "Renderer.h"
#include <iostream>

extern const float paddle_width = 50;
extern const float paddle_height = 50;
extern State active = State::left;

void user_renderer(Renderer &r);

Renderer r(1280, 720, user_renderer);
Client client("localhost", 8080);
Game g(r, client);

void user_renderer(Renderer &r) { g.tick(); }

int main(int argc, char *argv[]) {

    if (std::string(argv[1]) == "right") {
        active = State::right;
    }

    const bool &running = r.get_status();
    while (running) {
        r.cycle_render();
    }

    return 0;
}
