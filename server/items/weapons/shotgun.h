//
// Created by ezequiel on 31/10/24.
//

#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "weapon.h"
#include <vector>

class Shotgun : public Weapon {

private:
    std::vector<Bullet> pellets_vector;
    int pellet_count;
    bool reloading;

public:

    Shotgun(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage,
            uint8_t range, uint8_t ammo_quantity, float recoil);

    bool isEmptyAmmo() override;

    std::unique_ptr<Bullet> shoot(bool is_aiming_up) override;

    bool isActive() override;

    void setReloadTime(int reload_time) override;

    int getReloadTime() override;

    void stopShooting() override;
};

#endif //SHOTGUN_H
