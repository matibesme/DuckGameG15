//
// Created by ezequiel on 02/11/24.

#include "pewpew_laser.h"


constexpr int BEAM_COUNT = 3;

PewPewLaser::PewPewLaser(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range, uint8_t ammo_quantity, float recoil) :
        Weapon(type, id, x_pos, y_pos, damage, range, ammo_quantity, recoil),
        beams_vector(),
        beam_count(BEAM_COUNT) {
    float maxSpread = 0.3;
    for (int i = 0; i < BEAM_COUNT; i++) {
        float spread = 0.0;

        if (i == 0) {
            spread = maxSpread;  // Bala de arriba
        } else if (i == 2) {
            spread = -maxSpread; // Bala de abajo
        }

        beams_vector.emplace_back(PEW_PEW_LASER_BULLET, i, 0, 0, damage, range, spread);
    }

}

bool PewPewLaser::isEmptyAmmo() {
    return ammo_quantity == 0;
}

std::unique_ptr<Bullet> PewPewLaser::shoot(bool is_aiming_up) {
    (void)is_aiming_up;
    if (isEmptyAmmo()) {
        return nullptr;
    }
    if (bullet_count > 2) {
        return nullptr;
    }
    switch (beam_count) {
        case 3:
            beam_count--;
            bullet_count += 1;
            if (direction == RIGHT) {
                beams_vector[0].release(x_pos + DUCK_WIDTH+ WIDTH_BULLET, y_pos + (DUCK_HEIGHT/2) , direction, true);
            } else if (direction == LEFT) {
                beams_vector[0].release(x_pos-WIDTH_BULLET, y_pos+ (DUCK_HEIGHT/2), direction, true);
            }
            return std::make_unique<Bullet>(beams_vector[0]);
        case 2:
            beam_count--;
            bullet_count += 1;
            if (direction == RIGHT) {
                beams_vector[1].release(x_pos + DUCK_WIDTH+ WIDTH_BULLET, y_pos + (DUCK_HEIGHT/2) , direction, true);
            } else if (direction == LEFT) {
                beams_vector[1].release(x_pos-WIDTH_BULLET, y_pos+ (DUCK_HEIGHT/2), direction, true);
            }
            return std::make_unique<Bullet>(beams_vector[1]);
        case 1:
            beam_count--;
            bullet_count += 1;
            ammo_quantity--;
            if (direction == RIGHT) {
                beams_vector[2].release(x_pos + DUCK_WIDTH+ WIDTH_BULLET, y_pos + (DUCK_HEIGHT/2) , direction, true);
            } else if (direction == LEFT) {
                beams_vector[2].release(x_pos-WIDTH_BULLET, y_pos+ (DUCK_HEIGHT/2), direction, true);
            }
            beam_count = BEAM_COUNT;
            return std::make_unique<Bullet>(beams_vector[2]);
        default:
            return nullptr;
    }
}


bool PewPewLaser::isActive() {
    return false;
}

void PewPewLaser::setReloadTime(int reload_time_) {
    reload_time = reload_time_;
}

int PewPewLaser::getReloadTime() {
    return reload_time;
}

void PewPewLaser::stopShooting() {
    bullet_count = 0;
}
// Created by ezequiel on 02/11/24
