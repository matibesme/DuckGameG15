#ifndef BOX_H
#define BOX_H

#include <cstdint>
#include <random>

#include <SDL2pp/Renderer.hh>
#include <SDL_render.h>

#include "Graficos.h"
#include "sound.h"

class Box {
public:
  // Constructor
  Box(uint8_t id, float initial_pos_x, float initial_pos_y, Graficos &graficos);

  // Dibuja la caja en pantalla, si no ha sido destruida
  void draw(SDL2pp::Renderer &renderer);

  // Actualiza la posicion de la caja
  void update(uint8_t type);

  float getX();
  float getY();

private:
  Graficos &graficos;
  uint8_t idBox;
  float pos_x, pos_y;
  uint8_t typeOfAction;
  int explosionSpriteX;
  Sound sound;
  void reproducirSonido();
};

#endif
