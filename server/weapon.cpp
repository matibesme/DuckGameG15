
#include "weapon.h"

Weapon::Weapon(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range, uint8_t ammo):
        Objeto(type, id, x_pos, y_pos),
        damage(damage),
        range(range),
        ammo(ammo),
        id(id) {}




uint8_t Weapon::getAmmo() {
    return ammo;
}

void Weapon::setAmmo(uint8_t ammo) {
    this->ammo = ammo;
}

void Weapon::shoot() {
    if (ammo == 0) {
        return;
    }
    ammo--;
}

void Weapon::setId(uint8_t id) {
    this->id = id;
}

uint8_t Weapon::getId() {
    return id;
}