#include "Paddle.h"
#include "Renderer.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>

#include <iostream>

Paddle p(100, 100);

void user_renderer(Renderer &r) { p.render_paddle(r); }

int main() {
    Renderer r(1280, 720, *user_renderer);

    const bool &running = r.get_status();
    const bool *&keys = r.get_keys();
    const float &dt = r.get_dt();

    while (running) {
        r.cycle_render();
        p.handle_input(keys, dt);
    }

    return 0;
}
