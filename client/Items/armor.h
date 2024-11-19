#ifndef ARMOR_H
#define ARMOR_H

#include "../common/common_constant.h"
#include "SDL2pp/SDL2pp.hh"

#include "Graficos.h"

using SDL2pp::Rect;
using SDL2pp::Renderer;
using SDL2pp::Texture;

class Armor {
private:
  Graficos &graficos;
  bool is_equipped;
  float pos_x;
  float pos_y;

public:
  Armor(Graficos &graficos, float pos_x, float pos_y);
  void draw(bool isFliped, SDL2pp::Renderer &renderer, bool isOnGround,
            bool isOnDuck);
  void update(float new_x, float new_y);

  float getPosX();

  float getPosY();
};

#endif
