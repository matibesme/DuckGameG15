//
// Created by matibesme on 24/10/24.
//

#include "bullet.h"

#include "constant_definitons.h"

Bullet::Bullet(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range):
    Objeto(type, id, x_pos, y_pos),
    damage(damage),
    range(range),
    is_alive(true)
    {}


uint8_t Bullet::getDamage() {
    return damage;
}

uint8_t Bullet::getRange() {
    return range;
}

bool Bullet::isAlive() {
    return this->is_alive;
}

uint8_t Bullet::getTypeOfBullet() {
    return type;
}

Bullet::~Bullet() {
    // Limpieza, si es necesaria
}


