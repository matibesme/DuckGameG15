#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <list>

#include "Graficos.h"
#include "SDL2pp/SDL2pp.hh"
#include "dto_definitions.h"
#include <map>

class Platform {
private:
  Graficos &graficos;
  uint8_t id;
  float pos_x;
  float pos_y;
  uint8_t type;
  float width;
  float height;

public:
  Platform(float initial_pos_x, float initial_pos_y, Graficos &graficos,
           uint8_t type, float width, float height);
  void draw();
  float getX();
  float getY();
};

#endif
