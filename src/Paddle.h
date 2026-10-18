#pragma once

#include "Object.h"
#include "Renderer.h"

class Paddle : public Object {
  public:
    Paddle(float x, float y) : Object(x, y) {}
    void render(Renderer &r);
    void handle_input(const bool *keys, float dt);
};
