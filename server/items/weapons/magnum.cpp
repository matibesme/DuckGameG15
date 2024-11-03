#include "magnum.h"

Magnum::Magnum(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage,
uint8_t range, uint8_t ammo_quantity, float recoil) : 
    Weapon(type, id, x_pos, y_pos, damage, range, ammo_quantity, recoil) ,
    bala(MAGNUM_BULLET, 1, 0, 0, 10, 250, 0.3) {}

bool Magnum::isEmptyAmmo() {
    return ammo_quantity == 0;
}

std::unique_ptr<Bullet> Magnum::shoot() {
    ammo_quantity--;

    bala.release(x_pos, y_pos, direction);
    if (direction == RIGHT) {
        setXPos(x_pos - recoil);
    } else  if (direction == LEFT) {
        setXPos(x_pos + recoil);
    }
    return std::make_unique<Bullet>(bala);
}

