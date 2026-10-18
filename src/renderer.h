#include <SDL3/SDL.h>
class Renderer {
  private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
};
