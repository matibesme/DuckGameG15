
#include "weapon.h"

Weapon::Weapon(uint8_t damage, uint8_t range, uint8_t ammo): damage(damage), range(range), ammo(ammo) {}




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