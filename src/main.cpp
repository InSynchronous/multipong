#include "Renderer.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>

void user_renderer(Renderer &r) {
    r.render_rectangle({100, 100, 200, 200}, {255, 80, 80, 255});
}

int main() {
    Renderer r(1280, 720, *user_renderer);

    const bool &running = r.get_status();

    while (running) {
        r.cycle_render();
    }

    return 0;
}
