#ifndef MAGNUM_H
#define MAGNUM_H

#include "weapon.h"

class Magnum: public Weapon {

private:
    Bullet bala;

public:
    Magnum(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range,
           uint8_t ammo_quantity, float recoil);

    bool isEmptyAmmo() override;

    std::unique_ptr<Bullet> shoot() override;

    bool isActive() override;

    void setReloadTime(int reload_time) override;
    int getReloadTime() override;
    void stopShooting() override;
};

#endif  // MAGNUM_H
