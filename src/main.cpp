#include "Renderer.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>

int main() {
    Renderer r(1280, 720);

    const bool &running = r.get_status();

    while (running) {
        r.cycle_render();
    }

    return 0;
}
