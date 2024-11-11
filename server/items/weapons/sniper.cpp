#include "sniper.h"
#

constexpr int RELOAD_TIME = 70;

Sniper::Sniper(uint8_t type, uint8_t id, float x_pos, float y_pos,
               uint8_t damage, uint8_t range, uint8_t ammo_quantity,
               float recoil)
    : Weapon(type, id, x_pos, y_pos, damage, range, ammo_quantity, recoil),
      bala(SNIPER_BULLET, 1, 0, 0, 10, range, 0) {}

bool Sniper::isEmptyAmmo() { return ammo_quantity == 0; }

std::unique_ptr<Bullet> Sniper::shoot(bool is_aiming_up) {
  if (isEmptyAmmo()) {
    return nullptr;
  }
  if (bullet_count > 0) {
    return nullptr;
  }
  if (reload_time != 0) {
    return nullptr;
  }
  ammo_quantity--;
  bullet_count += 1;
  reload_time = RELOAD_TIME;
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
  return std::make_unique<Bullet>(bala);
}

bool Sniper::isActive() { return false; }

void Sniper::setReloadTime(int reload_time_) { reload_time = reload_time_; }

int Sniper::getReloadTime() { return reload_time; }

void Sniper::stopShooting() { bullet_count = 0; }
