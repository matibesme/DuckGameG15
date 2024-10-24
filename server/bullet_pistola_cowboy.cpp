//
// Created by matibesme on 24/10/24.
//

#include "bullet_pistola_cowboy.h"

CowBoyBullet::CowBoyBullet (uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range):
    Bullet(type, id, x_pos, y_pos, damage, range),
    direction(DERECHA) {}

void CowBoyBullet::release(float x_pos, float y_pos) {
    this->x_pos = x_pos;
    this->y_pos = y_pos;
}

void CowBoyBullet::release(float x_pos, float y_pos, Direccion direction) {
    this->x_pos = x_pos;
    this->y_pos = y_pos;
    this->direction = direction;
}

void CowBoyBullet::executeAction() {
    if (is_alive && range > 0) {
        if (direction == DERECHA) {
            x_pos += 1;
        } else if (direction == IZQUIERDA) {
            x_pos -= 1;
        } else if (direction == ARRIBA) {
            y_pos -= 1;
        }
        range--;
        if (range == 0) {
            is_alive = false;
        }
    }
}
