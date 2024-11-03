//
// Created by ezequiel on 02/11/24.

#include "pewpew_laser.h"

#include "server/constant_definitons.h"

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

        beams_vector.emplace_back(S_ESCOPETA_BULLET, i, 0, 0, damage, range, spread);
    }

}

bool PewPewLaser::isEmptyAmmo() {
    return ammo_quantity == 0;
}

std::unique_ptr<Bullet> PewPewLaser::shoot() {
    if (isEmptyAmmo()) {
        return nullptr;
    }
    switch (beam_count) {
        case 3:
            beam_count--;
            beams_vector[0].release(x_pos, y_pos, direction, true);
            return std::make_unique<Bullet>(beams_vector[0]);
        case 2:
            beam_count--;
            beams_vector[1].release(x_pos, y_pos, direction, true);
            return std::make_unique<Bullet>(beams_vector[1]);
        case 1:
            beam_count--;
            ammo_quantity--;
            beams_vector[2].release(x_pos, y_pos, direction, true);
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

// Created by ezequiel on 02/11/24
