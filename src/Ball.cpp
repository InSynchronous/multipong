#include "Ball.h"

void Ball::render(Renderer &r) {
    r.render_circle({x, y, 10, 10}, {255, 255, 255, 255});
}
