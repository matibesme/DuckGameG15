
#include "weapon.h"

Weapon::Weapon(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range):
        Objeto(type, id, x_pos, y_pos),
        damage(damage),
        range(range),
        ammo_list() 
        {}

bool Weapon::isEmptyAmmo() {
    return ammo_list.empty();
}



Bullet& Weapon::shoot() {
    Bullet bullet = ammo_list.front();
    ammo_list.pop_front();
    bullet.release(x_pos, y_pos, direction);
    return bullet;
}

void Weapon::setId(uint8_t id) {
    this->id = id;
}

uint8_t Weapon::getId() {
    return id;
}