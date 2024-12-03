//
// Created by ezequiel on 02/11/24.

#include "pewpew_laser.h"

constexpr int BEAM_COUNT = 3;

PewPewLaser::PewPewLaser(uint8_t type, uint8_t id, float x_pos, float y_pos,
                         int damage, int range, int ammo_quantity, float recoil)
    : Weapon(type, id, x_pos, y_pos, damage, range, ammo_quantity, recoil),
      beams_vector(), beam_count(BEAM_COUNT) {
  float maxSpread = PEW_PEW_LASER_MAX_SPREAD;
  for (int i = CERO; i < BEAM_COUNT; i++) {
    float spread = NO_SPREAD;

    if (i == CERO) {
      spread = maxSpread; // Bala de arriba
    } else if (i == DOS) {
      spread = -maxSpread; // Bala de abajo
    }

    beams_vector.emplace_back(PEW_PEW_LASER_BULLET, i, CERO, CERO, damage, range,
                              spread);
  }
}

bool PewPewLaser::isEmptyAmmo() { return ammo_quantity == CERO; }

std::unique_ptr<Bullet> PewPewLaser::shoot(bool is_aiming_up) {
  if (isEmptyAmmo()) {
    return nullptr;
  }
  if (bullet_count > DOS) {
    return nullptr;
  }
  switch (beam_count) {
  case TRES:
    beam_count--;
    bullet_count += UNO;
    if (is_aiming_up and direction == RIGHT) {
      beams_vector[CERO].release(x_pos + DUCK_WIDTH - WIDTH_GUN / DOS,
                              y_pos - WIDTH_BULLET, BULLET_UP, true);
    } else if (is_aiming_up and direction == LEFT) {
      beams_vector[CERO].release(x_pos + HEIGHT_GUN / DOS, y_pos - WIDTH_BULLET,
                              BULLET_UP, true);
    } else if (direction == RIGHT) {
      beams_vector[CERO].release(x_pos + DUCK_WIDTH + WIDTH_BULLET,
                              y_pos + (DUCK_HEIGHT / DOS), direction, true);
    } else if (direction == LEFT) {
      beams_vector[CERO].release(x_pos - WIDTH_BULLET, y_pos + (DUCK_HEIGHT / DOS),
                              direction, true);
    }
    return std::make_unique<Bullet>(beams_vector[CERO]);
  case DOS:
    beam_count--;
    bullet_count += UNO;
    if (is_aiming_up and direction == RIGHT) {
      beams_vector[UNO].release(x_pos + DUCK_WIDTH - WIDTH_GUN / DOS,
                              y_pos - WIDTH_BULLET, BULLET_UP, true);
    } else if (is_aiming_up and direction == LEFT) {
      beams_vector[UNO].release(x_pos + HEIGHT_GUN / DOS, y_pos - WIDTH_BULLET,
                              BULLET_UP, true);
    } else if (direction == RIGHT) {
      beams_vector[UNO].release(x_pos + DUCK_WIDTH + WIDTH_BULLET,
                              y_pos + (DUCK_HEIGHT / DOS), direction, true);
    } else if (direction == LEFT) {
      beams_vector[UNO].release(x_pos - WIDTH_BULLET, y_pos + (DUCK_HEIGHT / DOS),
                              direction, true);
    }
    return std::make_unique<Bullet>(beams_vector[UNO]);
  case UNO:
    beam_count--;
    bullet_count += UNO;
    ammo_quantity--;
    if (is_aiming_up and direction == RIGHT) {
      beams_vector[DOS].release(x_pos + DUCK_WIDTH - WIDTH_GUN / DOS,
                              y_pos - WIDTH_BULLET, BULLET_UP, true);
    } else if (is_aiming_up and direction == LEFT) {
      beams_vector[DOS].release(x_pos + HEIGHT_GUN / DOS, y_pos - WIDTH_BULLET,
                              BULLET_UP, true);
    } else if (direction == RIGHT) {
      beams_vector[DOS].release(x_pos + DUCK_WIDTH + WIDTH_BULLET,
                              y_pos + (DUCK_HEIGHT / DOS), direction, true);
    } else if (direction == LEFT) {
      beams_vector[DOS].release(x_pos - WIDTH_BULLET, y_pos + (DUCK_HEIGHT / DOS),
                              direction, true);
    }
    beam_count = BEAM_COUNT;
    return std::make_unique<Bullet>(beams_vector[DOS]);
  default:
    return nullptr;
  }
}

bool PewPewLaser::isActive() { return false; }

void PewPewLaser::setReloadTime(int reload_time_) {
  reload_time = reload_time_;
}

int PewPewLaser::getReloadTime() { return reload_time; }

void PewPewLaser::stopShooting() { bullet_count = CERO; }
// Created by ezequiel on 02/11/24
