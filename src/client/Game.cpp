#include "Game.h"
#include "Client.h"
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
    for (auto o : renderables) {
        o->render(r, dt);
        o->handle_input(keys);
    }

    Paddle &p = (active == State::left) ? p1 : p2;
    ServerTelemetry response =
        c.sendClientTelemetry(active, p.w, p.a, p.s, p.d, p.blk);

    ball.x = response.ballx;
    ball.y = response.bally;
    p1.x = response.p1x;
    p1.y = response.p1y;
    p2.x = response.p2x;
    p2.y = response.p2y;

    std::string score = "Score: " + std::to_string(p1_points) + " : " +
                        std::to_string(p2_points);

    r.render_text(score.c_str(), 100.0f, 100.0f, {255, 255, 255, 255});
}
