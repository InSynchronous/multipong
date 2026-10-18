#pragma once

#include "Object.h"

class Ball : public Object {
  public:
    float x_vel = 0;
    float y_vel = 0;

    Ball(float x, float y) : Object(x, y) {}
    void render(Renderer &r, float dt);
    void handle_input(const bool *keys, float dt) {}
};
