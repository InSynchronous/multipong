#pragma once

#include "Object.h"

class Ball : public Object {
  private:
    float x_vel, y_vel;

  public:
    Ball(float x, float y) : Object(x, y) {}
    void render(Renderer &r);
    void handle_input(const bool *keys, float dt) {}
};
