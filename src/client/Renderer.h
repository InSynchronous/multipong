#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

template <typename T> struct Vector4 {
    T x, y, z, a;
};

class Renderer {
  private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    TTF_Font *font;
    TTF_TextEngine *engine;
    const bool *keys;

    bool running = true;
    int current_time;
    int last_time;
    float dt;

    int width, height;
    void (*user_render)(Renderer &);

    void set_color(Vector4<int> color);

  public:
    Renderer(int width, int height, void (*user_render)(Renderer &));

    const bool &get_status();
    const bool *&get_keys();

    const float &get_dt();

    void render_rectangle(Vector4<float> points, Vector4<int> color);
    void render_circle(Vector4<float> points, Vector4<int> color);
    void render_text(const char *text, float x, float y, Vector4<int> color);

    void cycle_render();
    void exit();
};
