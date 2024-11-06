#include "duel_pistol.h"

DuelPistol::DuelPistol(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage,
uint8_t range, uint8_t ammo_quantity, float recoil) : 
    Weapon(type, id, x_pos, y_pos, damage, range, ammo_quantity, recoil),
    bala(S_PISTOLA_DUELOS_BULLET, 1, 0, 0, 10, 250, 0.3) {}

bool DuelPistol::isEmptyAmmo() {
    return ammo_quantity == 0;
}

std::unique_ptr<Bullet> DuelPistol::shoot() {
    if (ammo_quantity == 0) {
        return nullptr;
    }
    if (bullet_count > 0) {
        return nullptr;
    }
    bullet_count += 1;
    ammo_quantity--;
  
    bala.release(x_pos, y_pos, direction, bala.randomSpread());
    if (direction == S_RIGTH) {
        setXPos(x_pos - recoil);
    } else  if (direction == S_LEFT) {
        setXPos(x_pos + recoil);
    }
    return std::make_unique<Bullet>(bala);
}

bool DuelPistol::isActive() {
    return false;
}

void DuelPistol::setReloadTime(int reload_time_) {
    reload_time = reload_time_;
}

int DuelPistol::getReloadTime() {
    return reload_time;
}

void DuelPistol::stopShooting() {
    bullet_count = 0;
}


