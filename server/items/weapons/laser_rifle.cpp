//
// Created by ezequiel on 05/11/24.
//

#include "laser_rifle.h"

constexpr float MAX_SPREAD_COUNTER = 0.5;

constexpr int BURST_INTERVAL = 5;

LaserRifle::LaserRifle(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range, uint8_t ammo_quantity, float recoil) :
        Weapon(type, id, x_pos, y_pos, damage, range, ammo_quantity, recoil),
        spread_counter(3),
        bullets_vector() {
    bullets_vector.emplace_back(LASER_RIFLE_BULLET, 1, 0, 0, damage, range, 3);
}

bool LaserRifle::isEmptyAmmo() {
    return ammo_quantity == 0;
}

std::unique_ptr<Bullet> LaserRifle::shoot() {
    if (isEmptyAmmo()) {
        return nullptr;
    }
    if (bullet_count % BURST_INTERVAL != 0) {
        bullet_count += 1;
        return nullptr;
    }
    ammo_quantity--;
    bullet_count += 1;
    Bullet actual_bullet = bullets_vector[0];
    actual_bullet.release(x_pos, y_pos, direction, true);
    if (spread_counter < MAX_SPREAD_COUNTER) {
        spread_counter -= 0.1;
    }
    bullets_vector.pop_back();
    bullets_vector.emplace_back(LASER_RIFLE_BULLET, 1, 0, 0, damage, range, spread_counter);
    return std::make_unique<Bullet>(actual_bullet);
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

void LaserRifle::stopShooting() {
    spread_counter = 3;
    bullet_count = 0;
    bullets_vector.pop_back();
    bullets_vector.emplace_back(LASER_RIFLE_BULLET, 1, 0, 0, damage, range, spread_counter);
}


