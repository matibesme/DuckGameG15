#ifndef COYBOY_PISTOL_H
#define COYBOY_PISTOL_H

#include "weapon.h"

class CowboyPistol : public Weapon {
private:
    Bullet bala;
public:
    CowboyPistol(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range, uint8_t ammo_quantity, float recoil);

    bool isEmptyAmmo() override;

    std::unique_ptr<Bullet> shoot() override;

    bool isActive() override;

    void setReloadTime(int reload_time) override;

    int getReloadTime() override;

};


#endif //COYBOY_PISTOL_H
