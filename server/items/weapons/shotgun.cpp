//
// Created by ezequiel on 31/10/24.
//

#include "shotgun.h"

constexpr  int PELLET_COUNT = 6;

Shotgun::Shotgun(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range, uint8_t ammo_quantity, float recoil) :
        Weapon(type, id, x_pos, y_pos, damage, range, ammo_quantity, recoil),
        pellets_vector(),
        pellet_count(PELLET_COUNT) {
    float maxSpread = 0.3;
    int halfCount = PELLET_COUNT / 2; // Para dividir el número de balas a cada lado del cero

    for (int i = 0; i < PELLET_COUNT; i++) {
        // Calculamos el spread en función de la posición i
        float spread = maxSpread * (halfCount - i) / halfCount;
        pellets_vector.emplace_back(S_COWBOY_BULLET, i, 0, 0, damage, 250, spread);
    }
}

bool Shotgun::isEmptyAmmo() {
    return ammo_quantity == 0;
}

std::unique_ptr<Bullet> Shotgun::shoot() {
    if (ammo_quantity == 0) {
        return nullptr;
    }
    if (bullet_count > 5) {
        return nullptr;
    }

    if (reloading) {
        reloading = false;
        pellet_count = PELLET_COUNT;
        return nullptr;
    }

    switch (pellet_count) {
        case 6:
            pellet_count--;
            bullet_count += 1;
            pellets_vector[0].release(x_pos, y_pos, direction, true);
            return std::make_unique<Bullet>(pellets_vector[0]);
        case 5:
            pellet_count--;
            bullet_count += 1;
            pellets_vector[1].release(x_pos, y_pos, direction, true);
            return std::make_unique<Bullet>(pellets_vector[1]);
        case 4:
            pellet_count--;
            bullet_count += 1;
            pellets_vector[2].release(x_pos, y_pos, direction, true);
            return std::make_unique<Bullet>(pellets_vector[2]);
        case 3:
            pellet_count--;
            bullet_count += 1;
            pellets_vector[3].release(x_pos, y_pos, direction, true);
            return std::make_unique<Bullet>(pellets_vector[3]);
        case 2:
            pellet_count--;
            bullet_count += 1;
            pellets_vector[4].release(x_pos, y_pos, direction, true);
            return std::make_unique<Bullet>(pellets_vector[4]);
        case 1:
            pellet_count--;
            bullet_count += 1;
            reloading = true;
            ammo_quantity--;
            pellets_vector[5].release(x_pos, y_pos, direction, true);
            return std::make_unique<Bullet>(pellets_vector[5]);
        default:
            return nullptr;
    }
}

bool Shotgun::isActive() {
    return false;
}

void Shotgun::setReloadTime(int reload_time_) {
    reload_time = reload_time_;
}

int Shotgun::getReloadTime() {
    return reload_time;
}

void Shotgun::stopShooting() {
    bullet_count = 0;
    reloading = 1 - reloading;
}


