//
// Created by matibesme on 29/10/24.
//

#include "granada_bullet.h"

#include <iostream>


GranadaBullet::GranadaBullet(uint8_t type, uint8_t id, float x_pos, float y_pos,
                             int damage, int range, float spread,
                             uint8_t time_to_explode_)
    : Bullet(type, id, x_pos, y_pos, damage, range, spread),
      time_to_explode(time_to_explode_), velocidad(VELOCIDAD_INICIAL),
      continue_moving(true) {}

void GranadaBullet::executeAction() {
  if (time_to_explode > START_EXPLOTION && is_alive && continue_moving) {
    // Actualización de la posición vertical (y_pos)
    if (is_falling) {
      y_pos += std::abs(velocidad);
      if (velocidad < VEL_MAX) {
        velocidad += GRAVEDAD;
      }
    } else {
      y_pos -= velocidad;
      velocidad -= GRAVEDAD;
      if (velocidad == NULL_VEL) {
        is_falling = true;
      }
    }

    // Actualización de la posición horizontal (x_pos)
    x_pos += (direction == RIGHT ? RANGO_X_MEDIO : -RANGO_X_MEDIO);
  }

  // Lógica para la explosión y finalización de la vida
  if (time_to_explode == START_EXPLOTION) {
    explode();
  } else if (time_to_explode == CERO) {
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
        int min_distance = calculateCollisionSide(plat_x_pos, plat_y_pos,
                                                  plat_width, plat_height);
        if (min_distance == BULLET_UP) {
          continue_moving = false;
          y_pos = plat_y_pos - HEIGHT_GUN;
        } else {
          setIsFalling(true);
          if (min_distance == DOWN) {
            y_pos = plat_y_pos + plat_height + Y_SPACE;
          } else if (min_distance == LEFT) {
            x_pos = plat_x_pos - WIDTH_BIG_BULLET;
          } else if (min_distance == RIGHT) {
            x_pos = plat_x_pos + plat_width + X_SPACE;
          }
        }
      }
    }
  }
}

void GranadaBullet::boxExplosion(float x_pos, float y_pos,
                                 uint8_t time_to_explode_) {
  release(x_pos, y_pos, CERO, CERO);
  time_to_explode = time_to_explode_;
}

uint8_t GranadaBullet::calculateCollisionSide(float plat_x_pos,
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

  return CERO; // En caso de que ninguna coincidencia sea encontrada
}

void GranadaBullet::setIsExplode(bool is_explode_) {
  // esto es la punta izquierda de la granada pero quiero que la explosion sea
  // en el centro

  is_explode = is_explode_;
}

bool GranadaBullet::isExplode() { return is_explode; }
