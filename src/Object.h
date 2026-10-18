#pragma once

#include "Renderer.h"

class Object {
  public:
    float x, y;

    Object(float x, float y) : x(x), y(y) {}

    virtual void render(Renderer &r, float dt) = 0;
    virtual void handle_input(const bool *keys, float dt) = 0;
};
