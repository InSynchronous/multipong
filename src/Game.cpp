#include "Game.h"
#include <cstdlib>
#include <iostream>

extern const float paddle_height, paddle_width;

void Game::tick() {
    ball.x += ball.x_vel * dt;
    ball.y += ball.y_vel * dt;

    // bouncy ball
    if (ball.x < (p1.x + paddle_width) && ball.x > p1.x && ball.y > p1.y &&
        ball.y < (p1.y + paddle_height)) {
        ball.x = p1.x + paddle_width;
        ball.x_vel *= -1.1;
        ball.y_vel *= -1.1;
    }

    if (ball.x > p2.x && ball.x < (p2.x + paddle_width) && ball.y > p2.y &&
        ball.y < (p2.y + paddle_height)) {
        ball.x = p2.x;
        ball.x_vel *= -1.1;
        ball.y_vel *= -1.1;
    }

    for (auto o : renderables) {
        o->render(r);
        o->handle_input(keys, dt);
    }
}
