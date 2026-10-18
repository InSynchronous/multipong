#include "Paddle.h"

void Paddle::render_paddle(Renderer &r) {
    r.render_rectangle({x, y, 50, 200}, {255, 80, 80, 255});
}

void Paddle::handle_input(const bool *keys, float dt) {
    float speed = 700.0f;
    if (keys[SDL_SCANCODE_S]) {
        y += speed * dt;
    }

    if (keys[SDL_SCANCODE_W]) {
        y -= speed * dt;
    }
}
