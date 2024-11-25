#include "armor.h"

#include <SDL_render.h>

#define IMAGE_ARMOR DATA_PATH "/armour/pechera.png"

Armor::Armor(Graficos &graficos, float pos_x, float pos_y)
    : graficos(graficos), pos_x(pos_x), pos_y(pos_y) {}

void Armor::draw(bool isFliped, SDL2pp::Renderer &renderer, bool isOnGround,
                 bool isOnDuck) {
  Texture texture(graficos.LoadTexture(IMAGE_ARMOR));

  if (isOnDuck) {
    if (isOnGround) {
      if (isFliped)
        renderer.Copy(texture, SDL2pp::NullOpt,
                      Rect(pos_x + DUCK_WIDTH / 6, pos_y + DUCK_HEIGHT / 4,
                           WIDTH_ARMOR, HEIGHT_ARMOR),
                      90.0, SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
      else
        renderer.Copy(texture, SDL2pp::NullOpt,
                      Rect(pos_x + DUCK_WIDTH / 4, pos_y + DUCK_HEIGHT / 4,
                           WIDTH_ARMOR, HEIGHT_ARMOR),
                      270.0);
    } else {
      if (isFliped)
        renderer.Copy(texture, SDL2pp::NullOpt,
                      Rect(pos_x + DUCK_WIDTH / 9 + 1, pos_y + 3, WIDTH_ARMOR,
                           HEIGHT_ARMOR),
                      0.0, SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
      else
        renderer.Copy(texture, SDL2pp::NullOpt,
                      Rect(pos_x + DUCK_WIDTH * 0.15, pos_y + 3, WIDTH_ARMOR,
                           HEIGHT_ARMOR));
    }
  } else {
    renderer.Copy(texture, SDL2pp::NullOpt,
                  Rect(pos_x, pos_y, WIDTH_ARMOR * 2, HEIGHT_ARMOR));
  }
}

void Armor::update(float new_x, float new_y) {
  pos_x = new_x;
  pos_y = new_y;
}

float Armor::getPosX() { return pos_x; }

float Armor::getPosY() { return pos_y; }
