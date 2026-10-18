#include <SDL3/SDL.h>

template <typename T> struct Vector4 {
    T x, y, z, a;
};

class Renderer {
  private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    bool running;

    int width, height;
    void (*user_render)(Renderer &);

    void set_color(Vector4<int> color);

  public:
    Renderer(int width, int height, void (*user_render)(Renderer &));

    const bool &get_status();

    void render_rectangle(Vector4<float> points, Vector4<int> color);

    void cycle_render();
    void exit();
};
