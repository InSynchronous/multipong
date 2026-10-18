#include "Game.h"
#include "Renderer.h"

extern const float paddle_width = 50;
extern const float paddle_height = 50;
extern State active = State::left;

void user_renderer(Renderer &r);

Renderer r(1280, 720, user_renderer);
Game g(r);

void user_renderer(Renderer &r) { g.tick(); }

int main() {

    const bool &running = r.get_status();
    while (running) {
        r.cycle_render();
    }

    return 0;
}
