//
// Created by matibesme on 29/10/24.
//

#include "granada.h"

Granada::Granada(uint8_t type, uint8_t id, float x_pos, float y_pos,
                 uint8_t damage, uint8_t range, int ammo_quantity, float recoil)
    : Weapon(type, id, x_pos, y_pos, damage, range, ammo_quantity, recoil),
      bala(GRANADA_BULLET, 1, 0, 0, 10, range, 0.3, GRANADA_TIME_TO_EXPLODE),
      counter_to_shoot(COUNTER_TO_SHOOT_GRANADA),
      time_to_explode(GRANADA_TIME_TO_EXPLODE) {}

bool Granada::isEmptyAmmo() { return ammo_quantity == 0; }

bool Granada::isActive() {
  if (counter_to_shoot == 0) {
    time_to_explode--;
    return time_to_explode == 6;
  }

  return false;
}

std::unique_ptr<Bullet> Granada::shoot(bool is_aiming_up) {
  (void)is_aiming_up;
  if (bullet_count > 0) {
    return nullptr;
  }
  if (counter_to_shoot != 0) {
    counter_to_shoot--;
    return nullptr;
  }
  bullet_count += 1;
  ammo_quantity--;
  if (is_aiming_up and direction == RIGHT) {
    bala.release(x_pos + DUCK_WIDTH - WIDTH_GUN / 2, y_pos - WIDTH_BULLET,
                 BULLET_UP, time_to_explode);
  } else if (is_aiming_up and direction == LEFT) {
    bala.release(x_pos + HEIGHT_GUN / 2, y_pos - WIDTH_BULLET, BULLET_UP,
                 time_to_explode);
  } else if (direction == RIGHT) {
    bala.release(x_pos + DUCK_WIDTH + WIDTH_BULLET, y_pos + (DUCK_HEIGHT / 2),
                 direction, time_to_explode);
  } else if (direction == LEFT) {
    bala.release(x_pos - WIDTH_BULLET, y_pos + (DUCK_HEIGHT / 2), direction,
                 time_to_explode);
  }
  if (direction == RIGHT) {
    setXPos(x_pos - recoil);
  } else if (direction == LEFT) {
    setXPos(x_pos + recoil);
  }
  counter_to_shoot = COUNTER_TO_SHOOT_GRANADA;
  time_to_explode = GRANADA_TIME_TO_EXPLODE;
  return std::make_unique<GranadaBullet>(bala);
}

void Granada::setReloadTime(int reload_time_) { reload_time = reload_time_; }

int Granada::getReloadTime() { return reload_time; }

void Granada::stopShooting() { bullet_count = 0; }
