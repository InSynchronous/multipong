#pragma once

#include "Object.h"

class Ball : public Object {
  public:
    float x_vel = -500;
    float y_vel = -100;

    Ball(float x, float y) : Object(x, y) {}
    void render(Renderer &r);
    void handle_input(const bool *keys, float dt) {}
};
