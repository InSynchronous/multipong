#include "GameServer.h"

#include <algorithm>
#include <cmath>

namespace {
constexpr uint8_t INPUT_P1 = 1u << 0;
constexpr uint8_t INPUT_P2 = 1u << 1;
constexpr uint8_t INPUT_W = 1u << 2;
constexpr uint8_t INPUT_A = 1u << 3;
constexpr uint8_t INPUT_S = 1u << 4;
constexpr uint8_t INPUT_D = 1u << 5;
constexpr uint8_t INPUT_BLK = 1u << 6;
} // namespace

void GameServer::reset() {
    ball.x = WIDTH / 2.0f;
    ball.y = HEIGHT / 2.0f;
    ball.x_vel = 0.0f;
    ball.y_vel = 0.0f;

    p1.x = 100.0f;
    p1.y = 260.0f;
    p2.x = 1130.0f;
    p2.y = 260.0f;

    p1.blocking = false;
    p2.blocking = false;

    speed = 200.0f;
    active = 0;
}

void GameServer::update_paddle(Paddle &paddle, uint8_t input, float dt) {
    const bool up = input & INPUT_W;
    const bool down = input & INPUT_S;
    const bool left = input & INPUT_A;
    const bool right = input & INPUT_D;

    if (up != down) {
        paddle.y += (up ? -1.0f : 1.0f) * PADDLE_SPEED * dt;
    }
    if (left != right) {
        paddle.x += (left ? -1.0f : 1.0f) * PADDLE_SPEED * dt;
    }

    paddle.x = std::clamp(paddle.x, 0.0f, WIDTH - PADDLE_WIDTH);
    paddle.y = std::clamp(paddle.y, 0.0f, HEIGHT - PADDLE_HEIGHT);

    paddle.blocking = input & INPUT_BLK;
}

void GameServer::update_ball(float dt) {
    Paddle &target = active == 0 ? p1 : p2;

    const float dx = target.x + PADDLE_WIDTH / 2.0f - ball.x;

    const float dy = target.y + PADDLE_HEIGHT / 2.0f - ball.y;

    const float magnitude = std::sqrt(dx * dx + dy * dy);

    if (magnitude > 0.001f) {
        ball.x_vel = dx / magnitude * speed;
        ball.y_vel = dy / magnitude * speed;
    }

    ball.x += ball.x_vel * dt;
    ball.y += ball.y_vel * dt;

    const bool hit = ball.x >= target.x && ball.x <= target.x + PADDLE_WIDTH &&
                     ball.y >= target.y && ball.y <= target.y + PADDLE_HEIGHT;

    if (!hit) {
        return;
    }

    if (!target.blocking) {
        if (active == 0) {
            ++p2_points;
        } else {
            ++p1_points;
        }

        reset();
        return;
    }

    speed *= 1.1f;
    active = 1 - active;
}

void GameServer::tick(uint8_t p1_input, uint8_t p2_input, float dt) {
    update_paddle(p1, p1_input, dt);
    update_paddle(p2, p2_input, dt);

    update_ball(dt);
}

ServerTelemetry GameServer::get_telemetry() const {
    return {ball.x, ball.y, p1.x, p1.y, p2.x, p2.y};
}
