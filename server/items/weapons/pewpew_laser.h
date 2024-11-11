//
// Created by ezequiel on 02/11/24.
//

#ifndef PEWPEW_LASER_H
#define PEWPEW_LASER_H

#include <vector>

#include "weapon.h"

class PewPewLaser: public Weapon {
private:
    std::vector<Bullet> beams_vector;
    int beam_count;

public:
    PewPewLaser(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range,
                uint8_t ammo_quantity, float recoil);


    bool isEmptyAmmo() override;

    std::unique_ptr<Bullet> shoot(bool is_aiming_up) override;

    bool isActive() override;

    void setReloadTime(int reload_time) override;

    int getReloadTime() override;

    void stopShooting() override;
};


#endif  // PEWPEW_LASER_H
