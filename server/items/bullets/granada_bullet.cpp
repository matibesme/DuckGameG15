//
// Created by matibesme on 29/10/24.
//

#include "granada_bullet.h"

GranadaBullet::GranadaBullet(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range, float spread,uint8_t time_to_explode_) :
        Bullet(type, id, x_pos, y_pos, damage, range, spread), time_to_explode(time_to_explode_), velocidad(20) , continue_moving(true) {}


void GranadaBullet::executeAction() {

  if (time_to_explode>6 && is_alive && continue_moving) {

    y_pos -= velocidad;
    velocidad -=GRAVEDAD;
    if (direction == S_RIGTH) {
      x_pos += S_RANGO_X_MEDIO;
    } else if (direction == S_LEFT) {
      x_pos -= S_RANGO_X_MEDIO;
    }

    if (y_pos >= S_POSICION_INICIAL_Y) {
      y_pos = S_POSICION_INICIAL_Y;
        continue_moving = false;
    }


  }

  if (time_to_explode == 6) explode();
  else if (time_to_explode == 0) {
    is_alive = false;
    return;
  }
    
  time_to_explode--;

}

void GranadaBullet::release_granada(float x_pos, float y_pos, uint8_t direction, uint8_t time_to_explode_) {
  release(x_pos, y_pos, direction, 0);
  time_to_explode = time_to_explode_;
}

void GranadaBullet::explode() {
  type = S_GRANADA_EXPLOTION;

}
