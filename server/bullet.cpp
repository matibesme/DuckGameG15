//
// Created by matibesme on 24/10/24.
//

#include "bullet.h"

#include "constant_definitons.h"

Bullet::Bullet(uint8_t damage, uint8_t range): Objeto(S_BULLET),
damage(damage), range(range) {
}


uint8_t Bullet::getDamage() {
    return damage;
}

uint8_t Bullet::getRange() {
    return range;
}

void Bullet::executeAction(){}

Bullet::~Bullet() {}
