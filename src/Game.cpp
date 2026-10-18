#include "Game.h"
#include <iostream>

void Game::tick() {
    std::cout << "Hi" << std::endl;
    p.handle_input(keys, dt);
    p.render_paddle(r);
}
