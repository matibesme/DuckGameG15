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
    if (direction == RIGHT) {
      x_pos += RANGO_X_MEDIO;
    } else if (direction == LEFT) {
      x_pos -= RANGO_X_MEDIO;
    }

    if (y_pos >= POSICION_INICIAL_Y) {
      y_pos = POSICION_INICIAL_Y;
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
  release(x_pos, y_pos, direction);
  time_to_explode = time_to_explode_;
}

void GranadaBullet::explode() {
  type = GRENADE_EXPLOSION;

}
