#include "Game.h"
#include <iostream>

void Game::tick() {
    for (auto o : renderables) {
        o->render(r);
        o->handle_input(keys, dt);
    }
}
