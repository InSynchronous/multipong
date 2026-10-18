#include "Paddle.h"

extern const float paddle_width, paddle_height;
extern State active;

void Paddle::render(Renderer &r, float dt) {
    r.render_rectangle({x, y, paddle_width, paddle_height},
                       {255, 80, static_cast<int>(blocking * 510), 255});

    if (blocking > 0) {
        blocking -= dt;
        if (blocking < 0)
            blocking = 0;
    }

    if (cooldown > 0) {
        cooldown -= dt;
        if (cooldown < 0)
            cooldown = 0;
    }
}

void Paddle::handle_input(const bool *keys, float dt) {
    float speed = 700.0f;
    if (active == state) {
        if (keys[SDL_SCANCODE_S]) {
            y += speed * dt;
        }

        if (keys[SDL_SCANCODE_W]) {
            y -= speed * dt;
        }

        if (keys[SDL_SCANCODE_D]) {
            x += speed * dt;
        }

        if (keys[SDL_SCANCODE_A]) {
            x -= speed * dt;
        }

        if (keys[SDL_SCANCODE_F] && cooldown <= 0) {
            blocking = 0.5;
            cooldown = blocking + 1;
        }
    }
}
