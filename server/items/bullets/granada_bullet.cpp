//
// Created by matibesme on 29/10/24.
//

#include "granada_bullet.h"

GranadaBullet::GranadaBullet(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range, float spread):
        Bullet(type, id, x_pos, y_pos, damage, range, spread), time_to_explode(S_GRANADA_TIME_TO_EXPLODE), velocidad(VELOCIDAD_INICIAL) {}


void GranadaBullet::executeAction() {

  if (is_alive && range > 0) {
    range--;
    y_pos -= velocidad;
    velocidad -=GRAVEDAD;
    if (direction == S_RIGTH) {
      x_pos += 2;
    } else if (direction == S_LEFT) {
      x_pos -= 2;
    }

    if (y_pos >= S_POSICION_INICIAL_Y) {
      y_pos = S_POSICION_INICIAL_Y;
  
    }
  } else if (time_to_explode > 0) {
    time_to_explode--;
  } else {
    is_alive = false;
  }
}
