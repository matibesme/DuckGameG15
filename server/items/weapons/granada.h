//
// Created by matibesme on 29/10/24.
//

#ifndef GRANADA_H
#define GRANADA_H
#include "weapon.h"
#include "../bullets/granada_bullet.h"


class Granada : public Weapon {
  private:
    GranadaBullet bala;

    public:
        Granada(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage,
        uint8_t range, uint8_t ammo_quantity, float recoil);
        bool isEmptyAmmo() override;
        std::unique_ptr<Bullet> shoot() override;

};



#endif //GRANADA_H
