#include "bullet.h"

#include <random>

Bullet::Bullet(uint8_t type, uint8_t id, float x_pos, float y_pos,
               uint8_t damage, uint8_t range, float spread)
    : Objeto(type, id, x_pos, y_pos), damage(damage), range(range),
      is_alive(true), spread(spread), spread_direction(false) {}

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
          changeDirection();
        } else {
          kill();
        }
      }
    }
  }
}

void Bullet::kill() { is_alive = false; }

void Bullet::setSpread(float spread) { this->spread = spread; }

void Bullet::changeDirection() {
  if (direction == RIGHT) {
    direction = LEFT;
  } else if (direction == LEFT) {
    direction = RIGHT;
  } else if (direction == BULLET_UP) {
    direction = DOWN;
  } else if (direction == DOWN) {
    direction = BULLET_UP;
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
  if (is_alive) {
    if (x_pos >= box_x_pos && x_pos <= box_x_pos + box_width) {
      if (y_pos >= box_y_pos && y_pos <= box_y_pos + box_height) {
        kill();
        return true;
      }
    }
  }
  return false;
}