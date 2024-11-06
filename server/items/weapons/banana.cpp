//
// Created by matibesme on 30/10/24.
//

#include "banana.h"

Banana::Banana(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range, uint8_t ammo_quantity, float recoil) :
    Weapon(type, id, x_pos, y_pos, damage, range, ammo_quantity, recoil),
    bala(S_BANANA_BULLET, 1, 0, 0, 10, 35, 0.3),
    counter_to_shoot(S_COUNTER_TO_SHOOT_GRANADA)
    {}

bool Banana::isEmptyAmmo() {
    return ammo_quantity == 0;
}
bool Banana::isActive() {
    return false;
}



std::unique_ptr<Bullet> Banana::shoot() {
    if (counter_to_shoot != 0) {
        counter_to_shoot--;
        return nullptr;
    }

    ammo_quantity--;

    bala.release(x_pos, y_pos, direction, bala.randomSpread());
    if (direction == S_RIGTH) {
        setXPos(x_pos - recoil);
    } else  if (direction == S_LEFT) {
        setXPos(x_pos + recoil);
    }
    counter_to_shoot = S_COUNTER_TO_SHOOT_GRANADA;
    return std::make_unique<BananaBullet>(bala);
}

void Banana::setReloadTime(int reload_time_) {
    reload_time = reload_time_;
}

int Banana::getReloadTime() {
    return reload_time;
}

void Banana::stopShooting() {

}


