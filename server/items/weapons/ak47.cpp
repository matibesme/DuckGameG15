//
// Created by ezequiel on 05/11/24.
//

#include "ak47.h"

constexpr int MAX_SPREAD_COUNTER = -1;

constexpr int BURST_INTERVAL = 5;

Ak47::Ak47(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range, uint8_t ammo_quantity, float recoil) :
        Weapon(type, id, x_pos, y_pos, damage, range, ammo_quantity, recoil),
        spread_counter(0),
        bullets_vector() {
    bullets_vector.emplace_back(AK47_BULLET, 1, 0, 0, damage, range, 0);
    }
bool Ak47::isEmptyAmmo() {
    return ammo_quantity == 0;
}

std::unique_ptr<Bullet> Ak47::shoot(bool is_aiming_up) {
    (void)is_aiming_up;
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
    if (direction == RIGHT) {
        actual_bullet.release(x_pos + DUCK_WIDTH+ WIDTH_BULLET, y_pos + (DUCK_HEIGHT/2) , direction, true);
    } else if (direction == LEFT) {
        actual_bullet.release(x_pos-WIDTH_BULLET, y_pos+ (DUCK_HEIGHT/2), direction, true);
    }
    if (spread_counter > MAX_SPREAD_COUNTER) {
        spread_counter -= 0.1;;
    }
    bullets_vector.pop_back();
    bullets_vector.emplace_back(AK47_BULLET, 1, 0, 0, damage, range, spread_counter);
    return std::make_unique<Bullet>(actual_bullet);
}

bool Ak47::isActive() {
    return false;
}

void Ak47::setReloadTime(int reload_time_) {
    reload_time = reload_time_;
}

int Ak47::getReloadTime() {
    return reload_time;
}

void Ak47::stopShooting() {
    spread_counter = 0;
    bullet_count = 0;
    bullets_vector.pop_back();
    bullets_vector.emplace_back(AK47_BULLET, 1, 0, 0, damage, range, 0);
}



