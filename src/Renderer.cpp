#include "Renderer.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

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

/*
disclaimer:
~~~not my code, i took it off stackoverflow and modified it to fit my usecase~~~
i'm too lazy to write one myself
*/

void Renderer::render_circle(Vector4<float> points, Vector4<int> color) {
    float cx = points.x;
    float cy = points.y;
    float radius = points.z;

    SDL_FColor sdl_color = {color.x / 255.0f, color.y / 255.0f,
                            color.z / 255.0f, color.a / 255.0f};

    const int segments = 32;

    std::vector<SDL_Vertex> vertices;
    vertices.reserve(segments + 2);

    vertices.push_back({{cx, cy}, sdl_color, {0.0f, 0.0f}});

    const float step = (2.0f * M_PI) / segments;
    for (int i = 0; i <= segments; i++) {
        float angle = i * step;
        float vx = cx + radius * cosf(angle);
        float vy = cy + radius * sinf(angle);
        vertices.push_back({{vx, vy}, sdl_color, {0.0f, 0.0f}});
    }

    std::vector<int> indices;
    indices.reserve(segments * 3);
    for (int i = 1; i <= segments; i++) {
        indices.push_back(0);     // center vertex
        indices.push_back(i);     // current perimeter vertex
        indices.push_back(i + 1); // next perimeter vertex
    }

    SDL_RenderGeometry(renderer, nullptr, vertices.data(), (int)vertices.size(),
                       indices.data(), (int)indices.size());
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
}

void Renderer::exit() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}
