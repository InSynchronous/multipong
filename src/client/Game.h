#pragma once

#include "../shared/State.h"
#include "Ball.h"
#include "Client.h"
#include "Object.h"
#include "Paddle.h"
#include <array>
#include <memory>

class Game {
  private:
    Paddle p1;
    Paddle p2;
    Ball ball;
    Renderer &r;
    Client &c;
    float speed = 200;

    int p1_points = 0;
    int p2_points = 0;

    std::array<Object *, 3> renderables = {&p1, &p2, &ball};
    const bool *&keys;
    const float &dt;

    void reset();

  public:
    Game(Renderer &r, Client &c)
        : ball(640, 360), p1(100, 260, State::left),
          p2(1130, 260, State::right), r(r), c(c), keys(r.get_keys()),
          dt(r.get_dt()) {}
    void tick();
};
