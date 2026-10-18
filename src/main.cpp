#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <iostream>

int main() {
    std::cout << "loading sdl" << std::endl;
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "sdl init failed!" << std::endl;
        return -1;
    }
    std::cout << "sdl loaded" << std::endl;

    SDL_Window *window =
        SDL_CreateWindow("my sdl3 app", 1280, 720, SDL_WINDOW_RESIZABLE);

    if (!window) {
        std::cout << "window init failed!" << std::endl;
        SDL_Quit();
        return -1;
    }

    std::cout << "sdl window opened" << std::endl;

    SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);

    if (!renderer) {
        std::cout << "renderer failed";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    std::cout << "renderer working" << std::endl;

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }

            if (event.type == SDL_EVENT_KEY_DOWN &&
                event.key.key == SDLK_ESCAPE) {
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

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
