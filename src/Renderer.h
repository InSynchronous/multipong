#include <SDL3/SDL.h>
class Renderer {
  private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    bool running;

    int width, height;

  public:
    Renderer(int width, int height);

    const bool &get_status();
    void cycle_render();
    void exit();
};
