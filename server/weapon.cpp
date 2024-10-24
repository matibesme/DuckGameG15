
#include "weapon.h"

Weapon::Weapon(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range):
        Objeto(type, id, x_pos, y_pos),
        damage(damage),
        range(range),
    
        id(id) {}





void Weapon::shoot() {
    
}

void Weapon::setId(uint8_t id) {
    this->id = id;
}

uint8_t Weapon::getId() {
    return id;
}