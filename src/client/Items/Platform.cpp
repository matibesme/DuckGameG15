#include "Platform.h"

#include <SDL_render.h>

#include "../common/common_constant.h"
#include "constantTextures.h"

Platform::Platform(float initial_pos_x, float initial_pos_y, Graficos &graficos,
                   uint8_t type, float width, float height)
    : graficos(graficos), pos_x(initial_pos_x), pos_y(initial_pos_y),
      type(type), width(width), height(height) {}

void Platform::draw() {
  Renderer &renderer = graficos.GetRenderer();
  SDL2pp::Texture *platform = nullptr;

    switch (type) {
  case TYPE_PLATFORM_DONUT:
    platform = &graficos.getTexture(IMAGE_PLATAFORMA_DONUT);
    break;
  case TYPE_PLATFORM_INDUSTRIAL:
    platform = &graficos.getTexture(IMAGE_PLATAFORMA_INDUSTRIAL);
    break;
  case TYPE_PLATFORM_NATURE:
    platform = &graficos.getTexture(IMAGE_PLATAFORMA_NATURE);
    break;
  case TYPE_PLATFORM_SPACE:
    platform = &graficos.getTexture(IMAGE_PLATAFORMA_SPACE);
    break;
  case TYPE_PLATFORM_UNDERGROUND:
    platform = &graficos.getTexture(IMAGE_PLATAFORMA_UNDERGROUND);
    break;
  case TYPE_PLATFORM_DONUT_LONG:
    platform = &graficos.getTexture(IMAGE_PLATAFORMA_DONUT_LONG);
    break;
  case TYPE_PLATFORM_NATURE_LONG:
    platform = &graficos.getTexture(IMAGE_PLATAFORMA_NATURE_LONG);
    break;
    // walls
  case TYPE_WALL_DONUT:
    platform = &graficos.getTexture(IMAGE_WALL_DONUT);
    break;
  case TYPE_WALL_NATURE:
    platform = &graficos.getTexture(IMAGE_WALL_NATURE);
    break;
  case TYPE_WALL_UNDERGROUND:
    platform = &graficos.getTexture(IMAGE_WALL_UNDERGROUND);
    break;
  }

  SDL2pp::Rect destRect(pos_x, pos_y, width, height);
  renderer.Copy(*platform, SDL2pp::NullOpt, destRect);
}

float Platform::getX() { return pos_x; }

float Platform::getY() { return pos_y; }
