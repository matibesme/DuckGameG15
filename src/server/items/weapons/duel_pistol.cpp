#include "duel_pistol.h"

DuelPistol::DuelPistol(uint8_t type, uint8_t id, float x_pos, float y_pos,
                       int damage, int range, int ammo_quantity, float recoil)
    : Weapon(type, id, x_pos, y_pos, damage, range, ammo_quantity, recoil),
      bala(PISTOLA_DUELOS_BULLET, UNO, CERO, CERO, damage, range,
           PISTOLA_DUELOS_SPREAD) {}

bool DuelPistol::isEmptyAmmo() { return ammo_quantity == CERO; }

std::unique_ptr<Bullet> DuelPistol::shoot(bool is_aiming_up) {
  if (ammo_quantity == CERO) {
    return nullptr;
  }
  if (bullet_count > CERO) {
    return nullptr;
  }
  bullet_count += UNO;
  ammo_quantity--;
  if (is_aiming_up and direction == RIGHT) {
    bala.release(x_pos + DUCK_WIDTH - WIDTH_GUN / DOS, y_pos - WIDTH_BULLET,
                 BULLET_UP, bala.randomSpread());
  } else if (is_aiming_up and direction == LEFT) {
    bala.release(x_pos + HEIGHT_GUN / DOS, y_pos - WIDTH_BULLET, BULLET_UP,
                 bala.randomSpread());
  } else if (direction == RIGHT) {
    bala.release(x_pos + DUCK_WIDTH + WIDTH_BULLET, y_pos + (DUCK_HEIGHT / DOS),
                 direction, bala.randomSpread());
  } else if (direction == LEFT) {
    bala.release(x_pos - WIDTH_BULLET, y_pos + (DUCK_HEIGHT / DOS), direction,
                 bala.randomSpread());
  }

  if (direction == RIGHT) {
    setXPos(x_pos - recoil);
  } else if (direction == LEFT) {
    setXPos(x_pos + recoil);
  }
  return std::make_unique<Bullet>(bala);
}

bool DuelPistol::isActive() { return false; }

void DuelPistol::setReloadTime(int reload_time_) { reload_time = reload_time_; }

int DuelPistol::getReloadTime() { return reload_time; }

void DuelPistol::stopShooting() { bullet_count = CERO; }
