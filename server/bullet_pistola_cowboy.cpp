//
// Created by matibesme on 24/10/24.
//

#include "bullet_pistola_cowboy.h"

CowBoyBullet::CowBoyBullet (uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range):
    Bullet(type, id, x_pos, y_pos, damage, range){}

void CowBoyBullet::release(float x_pos, float y_pos, uint8_t direction) {
    this->x_pos = x_pos;
    this->y_pos = y_pos;
    this->direction = direction;
}


void CowBoyBullet::executeAction() {
    if (is_alive && range > 0) {
        if (direction == S_RIGTH) {
            x_pos += 1;
        } else if (direction == S_LEFT) {
            x_pos -= 1;
        } else if (direction == S_UP) {
            y_pos -= 1;
        }
        range--;
        if (range == 0) {
            is_alive = false;
        }
    }
}


