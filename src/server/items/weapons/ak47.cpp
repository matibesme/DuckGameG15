//
// Created by ezequiel on 05/11/24.
//

#include "ak47.h"

constexpr int MAX_SPREAD_COUNTER = -1;

constexpr int BURST_INTERVAL = 5;

Ak47::Ak47(uint8_t type, uint8_t id, float x_pos, float y_pos, int damage,
           int range, int ammo_quantity, float recoil)
    : Weapon(type, id, x_pos, y_pos, damage, range, ammo_quantity, recoil),
      spread_counter(CERO), bullets_vector() {
  bullets_vector.emplace_back(AK47_BULLET, UNO, CERO, CERO, damage, range,
                              AK47_SPREAD_INITIAL);
}
bool Ak47::isEmptyAmmo() { return ammo_quantity == CERO; }

std::unique_ptr<Bullet> Ak47::shoot(bool is_aiming_up) {
  if (isEmptyAmmo()) {
    return nullptr;
  }
  if (bullet_count % BURST_INTERVAL != CERO) {
    bullet_count += UNO;
    return nullptr;
  }
  ammo_quantity--;
  bullet_count += CERO;
  Bullet actual_bullet = bullets_vector[CERO];
  if (is_aiming_up and direction == RIGHT) {
    actual_bullet.release(x_pos + DUCK_WIDTH - WIDTH_GUN / DOS,
                          y_pos - WIDTH_BULLET, BULLET_UP, true);
  } else if (is_aiming_up and direction == LEFT) {
    actual_bullet.release(x_pos + HEIGHT_GUN / DOS, y_pos - WIDTH_BULLET,
                          BULLET_UP, true);
  } else if (direction == RIGHT) {
    actual_bullet.release(x_pos + DUCK_WIDTH + WIDTH_BULLET,
                          y_pos + (DUCK_HEIGHT / DOS), direction, true);
  } else if (direction == LEFT) {
    actual_bullet.release(x_pos - WIDTH_BULLET, y_pos + (DUCK_HEIGHT / DOS),
                          direction, true);
  }
  if (spread_counter > MAX_SPREAD_COUNTER) {
    spread_counter -= SPREAD_VAR;
  }
  bullets_vector.pop_back();
  bullets_vector.emplace_back(AK47_BULLET, UNO, CERO, CERO, damage, range,
                              spread_counter);
  return std::make_unique<Bullet>(actual_bullet);
}

bool Ak47::isActive() { return false; }

void Ak47::setReloadTime(int reload_time_) { reload_time = reload_time_; }

int Ak47::getReloadTime() { return reload_time; }

void Ak47::stopShooting() {
  spread_counter = CERO;
  bullet_count = CERO;
  bullets_vector.pop_back();
  bullets_vector.emplace_back(AK47_BULLET, UNO, CERO, CERO, damage, range, CERO);
}
