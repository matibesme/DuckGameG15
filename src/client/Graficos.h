#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Items/constantTextures.h"
#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>
#include <string>

using SDL2pp::Renderer;
using SDL2pp::Surface;
using SDL2pp::Texture;
using SDL2pp::Window;

class Graficos {
public:
  Graficos(const char *title, int width, int height);
  Renderer &GetRenderer();
  Texture &getTexture(std::string path);
  void Clear();
  void show_window();

  Graficos(const Graficos &other) = delete;
  Graficos &operator=(const Graficos &other) = delete;
  Graficos(Graficos &&other) = delete;
  Graficos &operator=(Graficos &&other) = delete;

private:
  Window window;
  Renderer renderer;
  std::map<std::string, std::unique_ptr<SDL2pp::Texture>> textures;
  void loadAllTextures();
};

#endif // GRAPHICS_H
