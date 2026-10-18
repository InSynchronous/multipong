#include "Game.h"
#include <cmath>
#include <iostream>
#include <string>

extern const float paddle_height, paddle_width;
extern State active;

void Game::reset() {
    ball.x_vel = 0;
    ball.y_vel = 0;
    ball.x = 640;
    ball.y = 360;

    p1.x = 100;
    p1.y = 260;
    p2.x = 1130;
    p2.y = 260;

    speed = 200;

    active = State::left;
}

void Game::tick() {
    // bouncy ball
    if (active == State::left) {
        // homing ball
        float dx = (p1.x + paddle_width / 2.0f) - ball.x;
        float dy = (p1.y + paddle_height / 2.0f) - ball.y;
        float magnitude = std::sqrt(dx * dx + dy * dy);

        ball.x_vel = (dx / magnitude) * speed;
        ball.y_vel = (dy / magnitude) * speed;

        if (ball.x < (p1.x + paddle_width) && ball.x > p1.x && ball.y > p1.y &&
            ball.y < (p1.y + paddle_height)) {
            if (p1.blocking <= 0) {
                p2_points++;
                reset();
                return;
            }
            speed *= 1.1;
            active = State::right;
        }
    }

    if (active == State::right) {
        // homing ball
        float dx = (p2.x + paddle_width / 2.0f) - ball.x;
        float dy = (p2.y + paddle_height / 2.0f) - ball.y;
        float magnitude = std::sqrt(dx * dx + dy * dy);

        ball.x_vel = (dx / magnitude) * speed;
        ball.y_vel = (dy / magnitude) * speed;

        if (ball.x > p2.x && ball.x < (p2.x + paddle_width) && ball.y > p2.y &&
            ball.y < (p2.y + paddle_height)) {
            if (p2.blocking <= 0) {
                p1_points++;
                reset();
                return;
            }
            speed *= 1.1;
            active = State::left;
        }
    }

    ball.x += ball.x_vel * dt;
    ball.y += ball.y_vel * dt;

    for (auto o : renderables) {
        o->render(r, dt);
        o->handle_input(keys, dt);
    }

    std::string score = "Score: " + std::to_string(p1_points) + " : " +
                        std::to_string(p2_points);

    r.render_text(score.c_str(), 100.0f, 100.0f, {255, 255, 255, 255});
}
