//
// Created by matibesme on 30/10/24.
//

#include "banana_bullet.h"
//
// Created by matibesme on 29/10/24.
//


BananaBullet::BananaBullet(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range, float spread) :
        Bullet(type, id, x_pos, y_pos, damage, range, spread), velocidad(VELOCIDAD_INICIAL) , continue_moving(true) {}




void BananaBullet::executeAction() {

  if (is_alive && continue_moving) {

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
 
}

