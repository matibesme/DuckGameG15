
#include "weapon.h"

Weapon::Weapon(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range,uint8_t ammo_quantity):
        Objeto(type, id, x_pos, y_pos),
        damage(damage),
        range(range),
        ammo_quantity(ammo_quantity),
        bala(S_COWBOY_BULLET,1, 0,0,5,300)
        {}

bool Weapon::isEmptyAmmo() {
   return ammo_quantity == 0;
}

std::unique_ptr<Bullet> Weapon::shoot() {
    ammo_quantity--;
    bala.release(x_pos, y_pos, direction);
    return std::make_unique<CowBoyBullet>(bala);
}



