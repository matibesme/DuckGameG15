//
// Created by matibesme on 30/10/24.
//

#include "banana_bullet.h"
//
// Created by matibesme on 29/10/24.
//
#include <iostream>

BananaBullet::BananaBullet(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage,
                           uint8_t range, float spread):
        Bullet(type, id, x_pos, y_pos, damage, range, spread),
        velocidad(VELOCIDAD_INICIAL),
        continue_moving(true) {}


void BananaBullet::executeAction() {

    if (is_alive && continue_moving) {

        y_pos -= velocidad;
        velocidad -= GRAVEDAD;
        if (direction == RIGHT) {
            x_pos += RANGO_X_MEDIO;
        } else if (direction == LEFT) {
            x_pos -= RANGO_X_MEDIO;
        }
    }
}

void BananaBullet::colisionWithPlatform(float plat_x_pos, float plat_y_pos, float plat_width,
                                        float plat_height) {

    if (continue_moving && x_pos + WIDTH_BULLET >= plat_x_pos && x_pos <= plat_x_pos + plat_width) {

        if (y_pos + HEIGHT_GUN >= plat_y_pos && y_pos + HEIGHT_GUN + velocidad <= plat_y_pos) {
            y_pos = plat_y_pos - HEIGHT_GUN;
            continue_moving = false;

        } else if (y_pos + HEIGHT_GUN > plat_y_pos &&
                   y_pos + HEIGHT_GUN <= plat_y_pos + plat_height) {
            is_alive = false;
        }
    }
}