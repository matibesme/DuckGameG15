#include "duel_pistol.h"

DuelPistol::DuelPistol(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage,
uint8_t range, uint8_t ammo_quantity, float recoil) : 
    Weapon(type, id, x_pos, y_pos, damage, range, ammo_quantity, recoil) {}

bool DuelPistol::isEmptyAmmo() {
    return ammo_quantity == 0;
}

std::unique_ptr<Bullet> DuelPistol::shoot() {
    ammo_quantity--;
  
    bala.release(x_pos, y_pos, direction);
    if (direction == S_RIGTH) {
        setXPos(x_pos - recoil);
    } else  if (direction == S_LEFT) {
        setXPos(x_pos + recoil);
    }
    return std::make_unique<Bullet>(bala);
}



