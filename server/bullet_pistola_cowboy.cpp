//
// Created by matibesme on 24/10/24.
//

#include "bullet_pistola_cowboy.h"

CowBoyBullet::CowBoyBullet (uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range):
    Bullet(type, id, x_pos, y_pos, damage, range) {}


void CowBoyBullet::executeAction() {
    if (is_alive) {
        
    }
}
