//
// Created by ezequiel on 05/11/24.
//

#include "laser_rifle.h"

LaserRifle::LaserRifle(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range, uint8_t ammo_quantity, float recoil) :
        Weapon(type, id, x_pos, y_pos, damage, range, ammo_quantity, recoil),
        spread_counter(0),
        bullets_vector() {
    bullets_vector.emplace_back(S_LASER_RIFLE_BULLET, 1, 0, 0, damage, range, -1);
}

bool LaserRifle::isEmptyAmmo() {
    return ammo_quantity == 0;
}

std::unique_ptr<Bullet> LaserRifle::shoot() {
    return nullptr;
}

bool LaserRifle::isActive() {
    return false;
}

void LaserRifle::setReloadTime(int reload_time_) {
    reload_time = reload_time_;
}

int LaserRifle::getReloadTime() {
    return reload_time;
}

void LaserRifle::resetSpreadCounter() {
    spread_counter = 0;
}
