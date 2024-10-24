
#include "weapon.h"

Weapon::Weapon(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range):
        Objeto(type, id, x_pos, y_pos),
        damage(damage),
        range(range),
        bala(S_COWBOY_BULLET,1, 0,0,5,20)
        {}

bool Weapon::isEmptyAmmo() {
   // return ammo_list.empty();
   return false;
}

CowBoyBullet Weapon::shoot() {
    /*CowBoyBullet bullet = ammo_list.front();
    ammo_list.pop_front();
    bullet.release(x_pos, y_pos, direction);
    return bullet;*/
    return  bala;
}



