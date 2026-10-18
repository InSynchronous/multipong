#include "Game.h"
#include "Paddle.h"
#include "Renderer.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>

#include <iostream>

extern const float paddle_width = 50;
extern const float paddle_height = 200;

void user_renderer(Renderer &r);

Paddle p(100, 100);
Renderer r(1280, 720, user_renderer);
Game g(r);

void user_renderer(Renderer &r) { g.tick(); }

int main() {

    const bool &running = r.get_status();
    while (running) {
        r.cycle_render();
    }

    return 0;
}
