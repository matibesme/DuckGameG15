#ifndef BULLET_H
#define BULLET_H

#include "../common/common_constant.h"
#include "../sound.h"
#include "Graficos.h"
#include "SDL2pp/SDL2pp.hh"
#include <map>

class Bullet {
private:
  Graficos &graficos;          // Referencia a la clase Graficos
  uint8_t idBullet;            // Identificador de la bala
  float pos_x, pos_y;          // Posición de la bala
  uint8_t orientationOfBullet; // Si la bala está volteada o no
  uint8_t typeOfBullet;        // Tipo de bala
  int explosionSpriteX;        // Sprite de la explosión
  int iteracion;               // Iteración de la bala
  Sound sound;                 // Sonido de la bala
  void actualizarTipo(const char *&texture);
  void reproducirSonido();

public:
  // Constructor
  Bullet(uint8_t id, float initial_pos_x, float initial_pos_y,
         Graficos &graficos, uint8_t orientacion, uint8_t type);

  // Dibuja la bala en su posición actual
  void draw(SDL2pp::Renderer &renderer);

  // Actualiza la posición de la bala con nuevos valores
  void update(float new_pos_x, float new_pos_y, uint8_t type,
              uint8_t orientacion);

  uint8_t getId() const;
};

#endif // BULLET_H
