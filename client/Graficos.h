#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

class Graficos {
public:
    Graficos(const char* title, int width, int height);
    Renderer& GetRenderer();
    Texture LoadTexture(const char* path);
    void Clear();
    void show_window();

private:
    Window window;
    Renderer renderer;
};

#endif // GRAPHICS_H
