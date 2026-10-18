#include "Renderer.h"
#include <iostream>
#include <stdexcept>

Renderer::Renderer(int width, int height, void (*user_render)(Renderer &))
    : width(width), height(height), user_render(user_render) {

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

    last_time = SDL_GetTicks();
}

const bool &Renderer::get_status() { return running; }
const bool *&Renderer::get_keys() { return keys; }
const float &Renderer::get_dt() { return dt; }

void Renderer::set_color(Vector4<int> color) {
    SDL_SetRenderDrawColor(renderer, color.x, color.y, color.z, color.a);
}

void Renderer::render_rectangle(Vector4<float> points, Vector4<int> color) {
    SDL_FRect rect = {points.x, points.y, points.z, points.a};

    set_color(color);
    SDL_RenderFillRect(renderer, &rect);
}

void Renderer::cycle_render() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        }
    }

    current_time = SDL_GetTicks();
    dt = (current_time - last_time) / 1000.0f;
    last_time = current_time;

    SDL_PumpEvents();
    keys = SDL_GetKeyboardState(nullptr);

    SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
    SDL_RenderClear(renderer);

    user_render(*this);

    SDL_RenderPresent(renderer);
    SDL_Delay(16); // roughly 60 FPS
}

void Renderer::exit() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}
