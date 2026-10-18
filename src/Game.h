#pragma once

#include "Paddle.h"

class Game {
  private:
    Paddle p;
    Renderer &r;
    const bool *&keys;
    const float &dt;

  public:
    Game(Renderer &r) : p(100, 100), r(r), keys(r.get_keys()), dt(r.get_dt()) {}
    void tick();
};
