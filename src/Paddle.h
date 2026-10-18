#pragma once

#include "Object.h"
#include "Renderer.h"
#include "State.h"

class Paddle : public Object {
  private:
    const State state;
    float cooldown = 0;

  public:
    Paddle(float x, float y, State state) : Object(x, y), state(state) {}
    void render(Renderer &r, float dt);
    void handle_input(const bool *keys, float dt);

    float blocking = 0;
};
