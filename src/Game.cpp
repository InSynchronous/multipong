#include "Game.h"
#include <cmath>

extern const float paddle_height, paddle_width;
extern State active;

void Game::tick() {
    // bouncy ball
    if (active == State::left) {
        // homing ball
        float dx = (p1.x - ball.x);
        float dy = (p1.y - ball.y);
        float magnitude = std::sqrt(dx * dx + dy * dy);

        ball.x_vel = (dx / magnitude) * speed;
        ball.y_vel = (dy / magnitude) * speed;

        if (p1.blocking > 0 &&
            (ball.x < (p1.x + paddle_width) && ball.x > p1.x && ball.y > p1.y &&
             ball.y < (p1.y + paddle_height))) {
            ball.x = p1.x + paddle_width;
            speed *= 1.1;
            active = State::right;
        }
    }

    if (active == State::right) {
        // homing ball
        float dx = (p2.x - ball.x);
        float dy = (p2.y - ball.y);
        float magnitude = std::sqrt(dx * dx + dy * dy);

        ball.x_vel = (dx / magnitude) * speed;
        ball.y_vel = (dy / magnitude) * speed;

        if (p2.blocking > 0 &&
            (ball.x > p2.x && ball.x < (p2.x + paddle_width) && ball.y > p2.y &&
             ball.y < (p2.y + paddle_height))) {
            ball.x = p2.x;
            ball.x_vel *= -1.1;
            ball.y_vel *= -1.1;
            active = State::left;
        }
    }

    ball.x += ball.x_vel * dt;
    ball.y += ball.y_vel * dt;

    for (auto o : renderables) {
        o->render(r, dt);
        o->handle_input(keys, dt);
    }
}
