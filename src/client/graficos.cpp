#include "Graficos.h"

#include <SDL_image.h>

Graficos::Graficos(const char *title, int width, int height)
    : window(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
             height, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE),
      renderer(window, -1, SDL_RENDERER_ACCELERATED) {}

Renderer &Graficos::GetRenderer() { return renderer; }

Texture Graficos::LoadTexture(const char *path) {
  Surface surface(IMG_Load(path));
  return Texture(renderer, surface);
}

void Graficos::Clear() {
  renderer.SetDrawColor(0, 0, 0, 255);
  renderer.Clear();
}

void Graficos::show_window() { SDL_ShowWindow(window.Get()); }
