//
// Created by matibesme on 30/10/24.
//

#include "banana.h"

Banana::Banana(uint8_t type, uint8_t id, float x_pos, float y_pos,
               uint8_t damage, uint8_t range, uint8_t ammo_quantity,
               float recoil)
    : Weapon(type, id, x_pos, y_pos, damage, range, ammo_quantity, recoil),
      bala(BANANA_BULLET, 1, 0, 0, 10, 35, 0.3),
      counter_to_shoot(COUNTER_TO_SHOOT_GRANADA) {}

bool Banana::isEmptyAmmo() { return ammo_quantity == 0; }
bool Banana::isActive() { return false; }

std::unique_ptr<Bullet> Banana::shoot(bool is_aiming_up) {
  if (bullet_count > 0) {
    return nullptr;
  }
  if (counter_to_shoot != 0) {
    counter_to_shoot--;
    return nullptr;
  }
  if (isEmptyAmmo()) {
    return nullptr;
  }
  bullet_count += 1;
  ammo_quantity--;
  if (is_aiming_up and direction == RIGHT) {
    bala.release(x_pos + DUCK_WIDTH - WIDTH_GUN / 2, y_pos - WIDTH_BULLET,
                 BULLET_UP, bala.randomSpread());
  } else if (is_aiming_up and direction == LEFT) {
    bala.release(x_pos + HEIGHT_GUN / 2, y_pos - WIDTH_BULLET, BULLET_UP,
                 bala.randomSpread());
  } else if (direction == RIGHT) {
    bala.release(x_pos + DUCK_WIDTH + WIDTH_BULLET, y_pos + (DUCK_HEIGHT / 2),
                 direction, bala.randomSpread());
  } else if (direction == LEFT) {
    bala.release(x_pos - WIDTH_BULLET, y_pos + (DUCK_HEIGHT / 2), direction,
                 bala.randomSpread());
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

void Banana::stopShooting() { bullet_count = 0; }
