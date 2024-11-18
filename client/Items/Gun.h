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
  // Me tira error el pre-commit como que no lo uso
  float posX;
  float posY;
  uint8_t typeGun;
  std::unique_ptr<SDL2pp::Texture> texture_equipped;
  std::unique_ptr<SDL2pp::Texture> texture_not_equipped;
  void actualizarTextura(const char *&texture_path_equipped,
                         const char *&texture_path_not_equipped, int &width,
                         int &height);
  void cargarTextura();

public:
  Gun(Graficos &graficos, float pos_x, float pos_y, uint8_t typeOfGun);
  void drawOnDuck(float posX, float posY, bool isFliped, uint8_t typeOfGun,
                  bool lookingUp, SDL2pp::Renderer &renderer);
  void drawOnSpawn(SDL2pp::Renderer &renderer);
  float getPosX();
  float getPosY();
};

#endif