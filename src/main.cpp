#include "Game.h"
#include "Paddle.h"
#include "Renderer.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>

#include <iostream>

void user_renderer(Renderer &r);

Paddle p(100, 100);
Renderer r(1280, 720, user_renderer);
Game g(r);

void user_renderer(Renderer &r) { g.tick(); }

int main() {

    const bool &running = r.get_status();
    const bool *&keys = r.get_keys();
    const float &dt = r.get_dt();

    std::cout << running << std::endl;
    while (running) {
        r.cycle_render();
    }

    return 0;
}
