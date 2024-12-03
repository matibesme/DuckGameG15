//
// Created by ezequiel on 31/10/24.
//

#include "shotgun.h"

constexpr int PELLET_COUNT = 6;

Shotgun::Shotgun(uint8_t type, uint8_t id, float x_pos, float y_pos, int damage,
                 int range, int ammo_quantity, float recoil)
    : Weapon(type, id, x_pos, y_pos, damage, range, ammo_quantity, recoil),
      pellets_vector(), pellet_count(PELLET_COUNT) {
  float maxSpread = ESCOPETA_MAX_SPREAD;
  int halfCount =
      PELLET_COUNT / DOS; // Para dividir el número de balas a cada lado del cero

  for (int i = CERO; i < PELLET_COUNT; i++) {
    // Calculamos el spread en función de la posición i
    float spread = maxSpread * (halfCount - i) / halfCount;
    pellets_vector.emplace_back(COWBOY_BULLET, i, CERO, CERO, damage, range, spread);
  }
}

bool Shotgun::isEmptyAmmo() { return ammo_quantity == CERO; }

std::unique_ptr<Bullet> Shotgun::shoot(bool is_aiming_up) {
  if (ammo_quantity == CERO) {
    return nullptr;
  }
  if (bullet_count > CINCO) {
    return nullptr;
  }

  if (reloading) {
    reloading = false;
    pellet_count = PELLET_COUNT;
    return nullptr;
  }

  switch (pellet_count) {
  case 6:
    pellet_count--;
    bullet_count += UNO;
    if (is_aiming_up and direction == RIGHT) {
      pellets_vector[CERO].release(x_pos + DUCK_WIDTH - WIDTH_GUN / DOS,
                                y_pos - WIDTH_BULLET, BULLET_UP, true);
    } else if (is_aiming_up and direction == LEFT) {
      pellets_vector[CERO].release(x_pos + HEIGHT_GUN / DOS, y_pos - WIDTH_BULLET,
                                BULLET_UP, true);
    } else if (direction == RIGHT) {
      pellets_vector[CERO].release(x_pos + DUCK_WIDTH + WIDTH_BULLET,
                                y_pos + (DUCK_HEIGHT / DOS), direction, true);
    } else if (direction == LEFT) {
      pellets_vector[CERO].release(x_pos - WIDTH_BULLET, y_pos + (DUCK_HEIGHT / DOS),
                                direction, true);
    }

    return std::make_unique<Bullet>(pellets_vector[CERO]);
  case CINCO:
    pellet_count--;
    bullet_count += UNO;
    if (is_aiming_up and direction == RIGHT) {
      pellets_vector[UNO].release(x_pos + DUCK_WIDTH - WIDTH_GUN / DOS,
                                y_pos - WIDTH_BULLET, BULLET_UP, true);
    } else if (is_aiming_up and direction == LEFT) {
      pellets_vector[UNO].release(x_pos + HEIGHT_GUN / DOS, y_pos - WIDTH_BULLET,
                                BULLET_UP, true);
    } else if (direction == RIGHT) {
      pellets_vector[UNO].release(x_pos + DUCK_WIDTH + WIDTH_BULLET,
                                y_pos + (DUCK_HEIGHT / DOS), direction, true);
    } else if (direction == LEFT) {
      pellets_vector[UNO].release(x_pos - WIDTH_BULLET, y_pos + (DUCK_HEIGHT / DOS),
                                direction, true);
    }
    return std::make_unique<Bullet>(pellets_vector[UNO]);
  case CUATRO:
    pellet_count--;
    bullet_count += UNO;
    if (is_aiming_up and direction == RIGHT) {
      pellets_vector[DOS].release(x_pos + DUCK_WIDTH - WIDTH_GUN / DOS,
                                y_pos - WIDTH_BULLET, BULLET_UP, true);
    } else if (is_aiming_up and direction == LEFT) {
      pellets_vector[DOS].release(x_pos + HEIGHT_GUN / DOS, y_pos - WIDTH_BULLET,
                                BULLET_UP, true);
    } else if (direction == RIGHT) {
      pellets_vector[DOS].release(x_pos + DUCK_WIDTH + WIDTH_BULLET,
                                y_pos + (DUCK_HEIGHT / DOS), direction, true);
    } else if (direction == LEFT) {
      pellets_vector[DOS].release(x_pos - WIDTH_BULLET, y_pos + (DUCK_HEIGHT / DOS),
                                direction, true);
    }
    return std::make_unique<Bullet>(pellets_vector[DOS]);
  case TRES:
    pellet_count--;
    bullet_count += UNO;
    if (is_aiming_up and direction == RIGHT) {
      pellets_vector[TRES].release(x_pos + DUCK_WIDTH - WIDTH_GUN / DOS,
                                y_pos - WIDTH_BULLET, BULLET_UP, true);
    } else if (is_aiming_up and direction == LEFT) {
      pellets_vector[TRES].release(x_pos + HEIGHT_GUN / DOS, y_pos - WIDTH_BULLET,
                                BULLET_UP, true);
    } else if (direction == RIGHT) {
      pellets_vector[TRES].release(x_pos + DUCK_WIDTH + WIDTH_BULLET,
                                y_pos + (DUCK_HEIGHT / DOS), direction, true);
    } else if (direction == LEFT) {
      pellets_vector[TRES].release(x_pos - WIDTH_BULLET, y_pos + (DUCK_HEIGHT / DOS),
                                direction, true);
    }
    return std::make_unique<Bullet>(pellets_vector[TRES]);
  case DOS:
    pellet_count--;
    bullet_count += UNO;
    if (is_aiming_up and direction == RIGHT) {
      pellets_vector[CUATRO].release(x_pos + DUCK_WIDTH - WIDTH_GUN / DOS,
                                y_pos - WIDTH_BULLET, BULLET_UP, true);
    } else if (is_aiming_up and direction == LEFT) {
      pellets_vector[CUATRO].release(x_pos + HEIGHT_GUN / DOS, y_pos - WIDTH_BULLET,
                                BULLET_UP, true);
    } else if (direction == RIGHT) {
      pellets_vector[CUATRO].release(x_pos + DUCK_WIDTH + WIDTH_BULLET,
                                y_pos + (DUCK_HEIGHT / DOS), direction, true);
    } else if (direction == LEFT) {
      pellets_vector[CUATRO].release(x_pos - WIDTH_BULLET, y_pos + (DUCK_HEIGHT / DOS),
                                direction, true);
    }
    return std::make_unique<Bullet>(pellets_vector[CUATRO]);
  case UNO:
    pellet_count--;
    bullet_count += UNO;
    reloading = true;
    ammo_quantity--;
    if (is_aiming_up and direction == RIGHT) {
      pellets_vector[CINCO].release(x_pos + DUCK_WIDTH - WIDTH_GUN / DOS,
                                y_pos - WIDTH_BULLET, BULLET_UP, true);
    } else if (is_aiming_up and direction == LEFT) {
      pellets_vector[CINCO].release(x_pos + HEIGHT_GUN / DOS, y_pos - WIDTH_BULLET,
                                BULLET_UP, true);
    } else if (direction == RIGHT) {
      pellets_vector[CINCO].release(x_pos + DUCK_WIDTH + WIDTH_BULLET,
                                y_pos + (DUCK_HEIGHT / DOS), direction, true);
    } else if (direction == LEFT) {
      pellets_vector[CINCO].release(x_pos - WIDTH_BULLET, y_pos + (DUCK_HEIGHT / DOS),
                                direction, true);
    }
    return std::make_unique<Bullet>(pellets_vector[CINCO]);
  default:
    return nullptr;
  }
}

bool Shotgun::isActive() { return false; }

void Shotgun::setReloadTime(int reload_time_) { reload_time = reload_time_; }

int Shotgun::getReloadTime() { return reload_time; }

void Shotgun::stopShooting() {
  bullet_count = CERO;
  reloading = UNO - reloading;
}
