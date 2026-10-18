#pragma once

#include "Ball.h"
#include "Object.h"
#include "Paddle.h"
#include "State.h"
#include <array>
#include <memory>

class Game {
  private:
    Paddle p1;
    Paddle p2;
    Ball ball;
    Renderer &r;
    float speed = 200;

    std::array<Object *, 3> renderables = {&p1, &p2, &ball};
    const bool *&keys;
    const float &dt;

  public:
    Game(Renderer &r)
        : ball(640, 360), p1(100, 260, State::left),
          p2(1130, 260, State::right), r(r), keys(r.get_keys()),
          dt(r.get_dt()) {}
    void tick();
};
