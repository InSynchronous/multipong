#include "Renderer.h"
#include <iostream>
#include <stdexcept>

Renderer::Renderer(int width, int height) : width(width), height(height) {
    std::cout << "loading sdl" << std::endl;
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error("sdl init failed");
    }
    std::cout << "sdl loaded" << std::endl;

    window = SDL_CreateWindow("multipong", 1280, 720, SDL_WINDOW_RESIZABLE);

    if (!window) {
        SDL_Quit();
        throw std::runtime_error("window init failed!");
    }

    std::cout << "sdl window opened" << std::endl;

    renderer = SDL_CreateRenderer(window, nullptr);

    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw std::runtime_error("renderer failed");
    }
}

const bool &Renderer::get_status() { return running; }

void Renderer::cycle_render() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        }

        if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
            running = false;
        }
    }

    SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
    SDL_RenderClear(renderer);

    SDL_FRect rect = {100, 100, 200, 200};

    SDL_SetRenderDrawColor(renderer, 255, 80, 80, 255);
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);

    SDL_Delay(16); // roughly 60 FPS
}

void Renderer::exit() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}
