//
// Created by matibesme on 30/10/24.
//

#include "banana_bullet.h"
//
// Created by matibesme on 29/10/24.
//
#include <iostream>

BananaBullet::BananaBullet(uint8_t type, uint8_t id, float x_pos, float y_pos,
                           int damage, int range, float spread)
    : Bullet(type, id, x_pos, y_pos, damage, range, spread),
      velocidad(VELOCIDAD_INICIAL), continue_moving(true) {}

void BananaBullet::executeAction() {
  if (is_alive && continue_moving) {
    // Actualización de la posición vertical (y_pos)
    if (is_falling) {
      y_pos += std::abs(velocidad);
      if (velocidad < 15) {
        velocidad += GRAVEDAD;
      }
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
}

void BananaBullet::colisionWithPlatform(float plat_x_pos, float plat_y_pos,
                                        float plat_width, float plat_height) {
  if (is_alive) {
    if ((plat_x_pos < x_pos and x_pos < plat_x_pos + plat_width) or
        (plat_x_pos < x_pos + WIDTH_BIG_BULLET and
         x_pos + WIDTH_BIG_BULLET < plat_x_pos + plat_width)) {
      if ((plat_y_pos < y_pos and y_pos < plat_y_pos + plat_height) or
          (plat_y_pos < y_pos + HEIGHT_BIG_BULLET and
           y_pos + HEIGHT_BIG_BULLET < plat_y_pos + plat_height)) {
        int min_distance = calculateCollisionSide(plat_x_pos, plat_y_pos,
                                                  plat_width, plat_height);
        if (min_distance == BULLET_UP) {
          continue_moving = false;
          y_pos = plat_y_pos - HEIGHT_GUN;
        } else {
          setIsFalling(true);
          if (min_distance == DOWN) {
            y_pos = plat_y_pos + plat_height + 15;
          } else if (min_distance == LEFT) {
            x_pos = plat_x_pos - WIDTH_BIG_BULLET;
          } else if (min_distance == RIGHT) {
            x_pos = plat_x_pos + plat_width + 1;
          }
        }
      }
    }
  }
}

bool BananaBullet::colisionWithDuck(float duck_x_pos, float duck_y_pos,
                                    float duck_width, float duck_height) {
  if (continue_moving) {
    return false;
  }
  if (is_alive) {
    if ((duck_x_pos < x_pos and x_pos < duck_x_pos + duck_width) or
        (duck_x_pos < x_pos + WIDTH_BIG_BULLET and
         x_pos + WIDTH_BIG_BULLET < duck_x_pos + duck_width)) {
      if ((duck_y_pos < y_pos and y_pos < duck_y_pos + duck_height) or
          (duck_y_pos < y_pos + HEIGHT_BIG_BULLET and
           y_pos + HEIGHT_BIG_BULLET < duck_y_pos + duck_height)) {
        is_alive = false;
        return true;
      }
    }
  }
  return false;
}

uint8_t BananaBullet::calculateCollisionSide(float plat_x_pos,
                                              float plat_y_pos,
                                              float plat_width,
                                              float plat_height) {
  float up_distance =
      (y_pos +
       (type == LASER_RIFLE_BULLET ? HEIGHT_BULLET : HEIGHT_BIG_BULLET)) -
      plat_y_pos;
  float down_distance = (plat_y_pos + plat_height) - y_pos;
  float left_distance =
      (x_pos + (type == LASER_RIFLE_BULLET ? WIDTH_BULLET : WIDTH_BIG_BULLET)) -
      plat_x_pos;
  float right_distance = (plat_x_pos + plat_width) - x_pos;

  float min_distance =
      minimo(up_distance, down_distance, left_distance, right_distance);

  if (min_distance == up_distance) {
    if (!is_falling && y_pos + HEIGHT_BIG_BULLET > plat_y_pos + plat_height) {
      return DOWN;
    }
    return BULLET_UP;
  }
  if (min_distance == down_distance) {
    if (is_falling && y_pos < plat_y_pos) {
      return BULLET_UP;
    }
    return DOWN;
  }
  if (min_distance == left_distance) {
    return LEFT;
  }
  if (min_distance == right_distance) {
    return RIGHT;
  }

  return 0; // En caso de que ninguna coincidencia sea encontrada
}
