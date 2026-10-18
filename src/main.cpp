#include "Paddle.h"
#include "Renderer.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>

#include <iostream>

Paddle p(100, 100);

void user_renderer(Renderer &r) { p.render_paddle(r); }

void user_keyboard_handler(const bool *keys, float dt) {
    p.handle_input(keys, dt);
}

int main() {
    Renderer r(1280, 720, *user_renderer, *user_keyboard_handler);

    const bool &running = r.get_status();

    while (running) {
        r.cycle_render();
    }

    return 0;
}
