#include "bullet.h"

#include <random>

#include "granada_bullet.h"

Bullet::Bullet(uint8_t type, uint8_t id, float x_pos, float y_pos,
               uint8_t damage, uint8_t range, float spread)
    : Objeto(type, id, x_pos, y_pos), damage(damage), range(range),
      is_alive(true), spread(spread), spread_direction(false),
      is_falling(false) {}

uint8_t Bullet::getDamage() { return damage; }

uint8_t Bullet::getRange() { return range; }

bool Bullet::isAlive() { return this->is_alive; }

uint8_t Bullet::getTypeOfBullet() { return type; }

void Bullet::release(float x_pos, float y_pos, uint8_t direction,
                     bool spread_direction) {
  this->x_pos = x_pos;
  this->y_pos = y_pos;
  this->direction = direction;
  this->spread_direction = spread_direction;
}

bool Bullet::randomSpread() {
  // Inicializa el generador de números aleatorios con un "motor" de generación
  // aleatoria
  std::random_device rd; // fuente de entropía no determinista
  std::mt19937 gen(
      rd()); // motor generador de números aleatorios basado en Mersenne Twister

  // Distribución uniforme entre 0 y 1 para representar "falso" y "verdadero"
  std::bernoulli_distribution dist(0.5); // probabilidad de 50% para cada valor

  return dist(gen); // genera un valor verdadero o falso
}

void Bullet::executeAction() {
  if (is_alive && range > 0) {
    if (direction == RIGHT) {
      x_pos += BULLET_VEL;
      spread_direction ? y_pos += spread : y_pos -= spread;
    } else if (direction == LEFT) {
      x_pos -= BULLET_VEL;
      spread_direction ? y_pos += spread : y_pos -= spread;
    } else if (direction == BULLET_UP) {
      y_pos -= BULLET_VEL;
      spread_direction ? x_pos += spread : x_pos -= spread;
    } else if (direction == DOWN) {
      y_pos += BULLET_VEL;
      spread_direction ? x_pos += spread : x_pos -= spread;
    }
    range--;
    if (range == 0) {
      is_alive = false;
    }
  }
}

void Bullet::colisionWithPlatform(float plat_x_pos, float plat_y_pos,
                                  float plat_width, float plat_height) {
  if (is_alive) {
    if (x_pos >= plat_x_pos && x_pos <= plat_x_pos + plat_width) {
      if (y_pos >= plat_y_pos && y_pos <= plat_y_pos + plat_height) {
        if (type == LASER_RIFLE_BULLET) {
          changeDirection(calculateCollisionSide(plat_x_pos, plat_y_pos,
                                                 plat_width, plat_height));

        } else {
          kill();
        }
      }
    }
  }
}

float minimo(float a, float b, float c, float d) {
  float min_ab = (a < b) ? a : b;
  float min_cd = (c < d) ? c : d;
  return (min_ab < min_cd) ? min_ab : min_cd;
}

uint8_t Bullet::calculateCollisionSide(float plat_x_pos, float plat_y_pos,
                                       float plat_width, float plat_height) {
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
    return BULLET_UP;
  } else if (min_distance == down_distance) {
    if (is_falling) {
      return BULLET_UP;
    }
    return DOWN;
  } else if (min_distance == left_distance) {
    return LEFT;
  } else if (min_distance == right_distance) {
    return RIGHT;
  }

  return 0; // En caso de que ninguna coincidencia sea encontrada
}

void Bullet::kill() { is_alive = false; }

void Bullet::setSpread(float spread) { this->spread = spread; }

void Bullet::changeDirection(uint8_t where_colision) {
  switch (where_colision) {
  case BULLET_UP:
    spread_direction = !spread_direction;
    break;
  case DOWN:
    spread_direction = !spread_direction;
    break;
  case LEFT:
    direction = LEFT;
    break;
  case RIGHT:
    direction = RIGHT;
    break;
  default:
    break;
  }
}

bool Bullet::colisionWithDuck(float duck_x_pos, float duck_y_pos,
                              float duck_width, float duck_height) {
  if (is_alive) {
    if (x_pos >= duck_x_pos && x_pos <= duck_x_pos + duck_width) {
      if (y_pos >= duck_y_pos && y_pos <= duck_y_pos + duck_height) {
        kill();
        return true;
      }
    }
  }
  return false;
}

bool Bullet::colisionWithBox(float box_x_pos, float box_y_pos, float box_width,
                             float box_height) {
  if (is_alive and type != BANANA_BULLET and type != GRANADA_BULLET) {
    if (x_pos >= box_x_pos && x_pos <= box_x_pos + box_width) {
      if (y_pos >= box_y_pos && y_pos <= box_y_pos + box_height) {
        kill();
        return true;
      }
    }
  }
  return false;
}

void Bullet::setIsFalling(bool is_falling) { this->is_falling = is_falling; }
