#include "Ball.h"

void Ball::render(Renderer &r, float dt) {
    r.render_circle({x, y, 10, 10}, {255, 255, 255, 255});
}
