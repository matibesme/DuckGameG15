#ifndef MAGNUM_H
#define MAGNUM_H

#include "weapon.h"

class Magnum : public Weapon {
public:
    Magnum(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage,
    uint8_t range, uint8_t ammo_quantity, float recoil);

    bool isEmptyAmmo() override;

    std::unique_ptr<Bullet> shoot() override;
};

#endif //MAGNUM_H
