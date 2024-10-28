#ifndef DUEL_PISTOL_H
#define DUEL_PISTOL_H

#include "weapon.h"

class DuelPistol : public Weapon {
public:
    DuelPistol(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage,
    uint8_t range, uint8_t ammo_quantity, float recoil);

    bool isEmptyAmmo() override;

    std::unique_ptr<Bullet> shoot() override;
};

#endif //DUEL_PISTOL_H
