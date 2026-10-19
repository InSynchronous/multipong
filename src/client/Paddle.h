#pragma once

#include "../shared/State.h"
#include "Object.h"
#include "Renderer.h"

class Paddle : public Object {
  private:
    const State state;
    float cooldown = 0;

  public:
    Paddle(float x, float y, State state) : Object(x, y), state(state) {}
    void render(Renderer &r, float dt);
    void handle_input(const bool *keys);

    float blocking = 0;

    bool w = false, a = false, s = false, d = false, blk = false;
};
