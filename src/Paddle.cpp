#include "Paddle.h"

extern const float paddle_width, paddle_height;

void Paddle::render(Renderer &r) {
    r.render_rectangle({x, y, paddle_width, paddle_height}, {255, 80, 80, 255});
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
