//
// Created by matibesme on 30/10/24.
//

#include "banana.h"

Banana::Banana(uint8_t type, uint8_t id, float x_pos, float y_pos, int damage,
               int range, int ammo_quantity, float recoil)
    : Weapon(type, id, x_pos, y_pos, damage, range, ammo_quantity, recoil),
      bala(BANANA_BULLET, UNO, CERO, CERO, damage, range, BANANA_SPREAD),
      counter_to_shoot(COUNTER_TO_SHOOT_GRANADA) {}

bool Banana::isEmptyAmmo() { return ammo_quantity == CERO; }
bool Banana::isActive() { return false; }

std::unique_ptr<Bullet> Banana::shoot(bool is_aiming_up) {
  if (bullet_count > CERO) {
    return nullptr;
  }
  if (counter_to_shoot != CERO) {
    counter_to_shoot--;
    return nullptr;
  }
  if (isEmptyAmmo()) {
    return nullptr;
  }
  bullet_count += UNO;
  ammo_quantity--;
  if (is_aiming_up and direction == RIGHT) {
    bala.release(x_pos + DUCK_WIDTH - WIDTH_GUN / DOS, y_pos - WIDTH_BULLET,
                 BULLET_UP, true);
  } else if (is_aiming_up and direction == LEFT) {
    bala.release(x_pos + HEIGHT_GUN / DOS, y_pos - WIDTH_BULLET, BULLET_UP, true);
  } else if (direction == RIGHT) {
    bala.release(x_pos + DUCK_WIDTH + WIDTH_BULLET, y_pos + (DUCK_HEIGHT / DOS),
                 direction, true);
  } else if (direction == LEFT) {
    bala.release(x_pos - WIDTH_BULLET, y_pos + (DUCK_HEIGHT / DOS), direction,
                 true);
  }
  if (direction == RIGHT) {
    setXPos(x_pos - recoil);
  } else if (direction == LEFT) {
    setXPos(x_pos + recoil);
  }
  counter_to_shoot = COUNTER_TO_SHOOT_GRANADA;

  return std::make_unique<BananaBullet>(bala);
}

void Banana::setReloadTime(int reload_time_) { reload_time = reload_time_; }

int Banana::getReloadTime() { return reload_time; }

void Banana::stopShooting() { bullet_count = CERO; }
