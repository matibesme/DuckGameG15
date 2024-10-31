#include "sniper.h"
#

constexpr int RELOAD_TIME = 70;

Sniper::Sniper(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage,
               uint8_t range, uint8_t ammo_quantity, float recoil) :
    Weapon(type, id, x_pos, y_pos, damage, range, ammo_quantity, recoil),
    bala(S_SNIPER_BULLET, 1, 0, 0, 10, 64, 0){}

bool Sniper::isEmptyAmmo() {
    return ammo_quantity == 0;
}

std::unique_ptr<Bullet> Sniper::shoot() {
    if (reload_time != 0) {
        return nullptr;
    }
    ammo_quantity--;
    reload_time = RELOAD_TIME;
    bala.release(x_pos, y_pos, direction, bala.randomSpread());
    if (direction == S_RIGTH) {
        setXPos(x_pos - recoil);
    } else  if (direction == S_LEFT) {
        setXPos(x_pos + recoil);
    }
    return std::make_unique<Bullet>(bala);
}


bool Sniper::isActive() {
    return false;
}

void Sniper::setReloadTime(int reload_time_) {
    reload_time = reload_time_;
}

int Sniper::getReloadTime() {
    return reload_time;
}

