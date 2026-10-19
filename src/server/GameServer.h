#pragma once

#include "../shared/Packet.h"

class GameServer {
  private:
    struct Paddle {
        float x;
        float y;
        bool blocking = false;
    };

    struct Ball {
        float x = 640.0f;
        float y = 360.0f;
        float x_vel = 0.0f;
        float y_vel = 0.0f;
    };

    Paddle p1{100.0f, 260.0f};
    Paddle p2{1130.0f, 260.0f};
    Ball ball;

    float speed = 200.0f;

    // 0 = homing toward P1, 1 = homing toward P2
    int active = 0;

    int p1_points = 0;
    int p2_points = 0;

    static constexpr float WIDTH = 1280.0f;
    static constexpr float HEIGHT = 720.0f;
    static constexpr float PADDLE_WIDTH = 50.0f;
    static constexpr float PADDLE_HEIGHT = 50.0f;
    static constexpr float PADDLE_SPEED = 400.0f;

    void reset();
    void update_paddle(Paddle &paddle, uint8_t input, float dt);
    void update_ball(float dt);

  public:
    void tick(uint8_t p1_input, uint8_t p2_input, float dt);
    ServerTelemetry get_telemetry() const;

    int get_p1_points() const { return p1_points; }
    int get_p2_points() const { return p2_points; }
};
