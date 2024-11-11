#ifndef GUN_H
#define GUN_H

#include "../common/common_constant.h"
#include "SDL2pp/SDL2pp.hh"

#include "Graficos.h"

using namespace SDL2pp;

class Gun {
private:
  Graficos &graficos;
  uint8_t typeOfGun;
  bool is_equiped;
  float pos_x;
  float pos_y;
  bool lookingUp;
  void setEquip(bool equip);
  void actualizarTextura(const char *&texture_equipped,
                         const char *&texture_not_equipped, int &width,
                         int &height);

public:
  Gun(Graficos &graficos, float pos_x, float pos_y, uint8_t typeOfGun);
  void draw(bool isFliped, SDL2pp::Renderer &renderer);
  bool isEquipped();
  void setGun(uint8_t gun, bool look_up);
  void update(float d, float d1);
  float getPosX();
  float getPosY();
};

#endif