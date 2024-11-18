#ifndef GUN_H
#define GUN_H

#include "../common/common_constant.h"
#include "Graficos.h"
#include "SDL2pp/SDL2pp.hh"
#include <memory>

using namespace SDL2pp;

class Gun {
private:
  Graficos &graficos;
  uint8_t typeOfGun;
  float pos_x;
  float pos_y;
  bool lookingUp;
  std::unique_ptr<SDL2pp::Texture> texture_equipped;
  std::unique_ptr<SDL2pp::Texture> texture_not_equipped;
  void actualizarTextura(const char *&texture_path_equipped,
                         const char *&texture_path_not_equipped, int &width,
                         int &height);
  void cargarTextura();

public:
  Gun(Graficos &graficos, float pos_x, float pos_y, uint8_t typeOfGun);
  void draw(bool isFliped, bool is_equiped, SDL2pp::Renderer &renderer);
  void updateGunState(uint8_t gun, bool look_up, float new_x, float new_y);
  float getPosX();
  float getPosY();
};

#endif