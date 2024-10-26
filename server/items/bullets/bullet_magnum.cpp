#include "bullet_magnum.h"

BulletMagnum::BulletMagnum(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range, float spread)
        : Bullet(type, id, x_pos, y_pos, damage, range, spread) {}

void BulletMagnum::executeAction() {
    if (is_alive && range > 0) {
        if (direction == S_RIGTH) {
            x_pos += 1;
            y_pos += spread;
        } else if (direction == S_LEFT) {
            x_pos -= 1;
            y_pos += spread;
        } else if (direction == S_UP) {
            y_pos -= 1;
            x_pos += spread;
        }
        range--;
        if (range == 0) {
            is_alive = false;
        }
    }
}