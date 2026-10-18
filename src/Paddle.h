#pragma once

#include "Renderer.h"

class Paddle {
  private:
    float x, y;

  public:
    Paddle(float x, float y) : x(x), y(y) {}
    void render_paddle(Renderer &r);
    void handle_input(const bool *keys, float dt);
};
