//
// Created by ezequiel on 05/11/24.
//

#include "laser_rifle.h"

constexpr float MAX_SPREAD_COUNTER = -1;

constexpr int BURST_INTERVAL = 5;

LaserRifle::LaserRifle(uint8_t type, uint8_t id, float x_pos, float y_pos,
                       int damage, int range, int ammo_quantity, float recoil)
    : Weapon(type, id, x_pos, y_pos, damage, range, ammo_quantity, recoil),
      spread_counter(TRES), bullets_vector() {
  bullets_vector.emplace_back(LASER_RIFLE_BULLET, UNO, CERO, CERO, damage,
                              range, LASER_RIFLE_SPREAD);
}

bool LaserRifle::isEmptyAmmo() { return ammo_quantity == CERO; }

std::unique_ptr<Bullet> LaserRifle::shoot(bool is_aiming_up) {
  (void)is_aiming_up;
  if (isEmptyAmmo()) {
    return nullptr;
  }
  if (bullet_count % BURST_INTERVAL != CERO) {
    bullet_count += UNO;
    return nullptr;
  }
  ammo_quantity--;
  bullet_count += UNO;
  Bullet actual_bullet = bullets_vector[CERO];
  if (is_aiming_up and direction == RIGHT) {
    actual_bullet.release(x_pos + DUCK_WIDTH - WIDTH_GUN / DOS,
                          y_pos - WIDTH_BULLET, RIGHT, false);
  } else if (is_aiming_up and direction == LEFT) {
    actual_bullet.release(x_pos + HEIGHT_GUN / DOS, y_pos - WIDTH_BULLET, LEFT,
                          false);
  } else if (direction == RIGHT) {
    actual_bullet.release(x_pos + DUCK_WIDTH + WIDTH_BULLET,
                          y_pos + (DUCK_HEIGHT / DOS), direction, true);
  } else if (direction == LEFT) {
    actual_bullet.release(x_pos - WIDTH_BULLET, y_pos + (DUCK_HEIGHT / DOS),
                          direction, true);
  }
  if (spread_counter < MAX_SPREAD_COUNTER) {
    spread_counter -= SPREAD_VAR;
  }
  bullets_vector.pop_back();
  bullets_vector.emplace_back(LASER_RIFLE_BULLET, UNO, CERO, CERO, damage,
                              range, spread_counter);
  return std::make_unique<Bullet>(actual_bullet);
}

bool LaserRifle::isActive() { return false; }

void LaserRifle::setReloadTime(int reload_time_) { reload_time = reload_time_; }

int LaserRifle::getReloadTime() { return reload_time; }

void LaserRifle::stopShooting() {
  spread_counter = TRES;
  bullet_count = CERO;
  bullets_vector.pop_back();
  bullets_vector.emplace_back(LASER_RIFLE_BULLET, UNO, CERO, CERO, damage,
                              range, spread_counter);
}
