//
// Created by matibesme on 29/10/24.
//

#include "granada_bullet.h"

#include <iostream>

GranadaBullet::GranadaBullet(uint8_t type, uint8_t id, float x_pos, float y_pos,
                             int damage, uint8_t range, float spread,
                             uint8_t time_to_explode_)
    : Bullet(type, id, x_pos, y_pos, damage, range, spread),
      time_to_explode(time_to_explode_), velocidad(VELOCIDAD_INICIAL),
      continue_moving(true) {}

void GranadaBullet::executeAction() {
  if (time_to_explode > 6 && is_alive && continue_moving) {
    // Actualización de la posición vertical (y_pos)
    if (is_falling) {
      y_pos += std::abs(velocidad);
      velocidad += GRAVEDAD;
    } else {
      y_pos -= velocidad;
      velocidad -= GRAVEDAD;
      if (velocidad == 0) {
        is_falling = true;
      }
    }

    // Actualización de la posición horizontal (x_pos)
    x_pos += (direction == RIGHT ? RANGO_X_MEDIO : -RANGO_X_MEDIO);
  }

  // Lógica para la explosión y finalización de la vida
  if (time_to_explode == 15) {
    explode();
  } else if (time_to_explode == 0) {
    is_alive = false;
    return;
  }

  time_to_explode--;
}

void GranadaBullet::release_granada(float x_pos, float y_pos, uint8_t direction,
                                    uint8_t time_to_explode_) {
  release(x_pos, y_pos, direction, false);
  time_to_explode = time_to_explode_;
}

void GranadaBullet::explode() { type = GRENADE_EXPLOSION; }

void GranadaBullet::colisionWithPlatform(float plat_x_pos, float plat_y_pos,
                                         float plat_width, float plat_height) {
  if (is_alive) {
    if ((plat_x_pos < x_pos and x_pos < plat_x_pos + plat_width) or
        (plat_x_pos < x_pos + WIDTH_BIG_BULLET and
         x_pos + WIDTH_BIG_BULLET < plat_x_pos + plat_width)) {
      if ((plat_y_pos < y_pos and y_pos < plat_y_pos + plat_height) or
          (plat_y_pos < y_pos + HEIGHT_BIG_BULLET and
           y_pos + HEIGHT_BIG_BULLET < plat_y_pos + plat_height)) {
        if (calculateCollisionSide(plat_x_pos, plat_y_pos, plat_width,
                                   plat_height) == BULLET_UP) {
          continue_moving = false;
          y_pos = plat_y_pos - HEIGHT_GUN;
        } else {
          setIsFalling(true);
          if (direction == RIGHT) {
            x_pos -= WIDTH_BIG_BULLET;
          } else if (direction == LEFT) {
            x_pos += WIDTH_BIG_BULLET;
          }
        }
      }
    }
  }
}

void GranadaBullet::boxExplosion(float x_pos, float y_pos,
                                 uint8_t time_to_explode_) {
  release(x_pos, y_pos, 0, 0);
  time_to_explode = time_to_explode_;
}
