#ifndef WEAPON_H
#define WEAPON_H
#include "objeto.h"
#include <cstdint>
#include <list>
#include "bullet.h"
#include "bullet_pistola_cowboy.h"
#include "constant_definitons.h"

class Weapon : public Objeto {
private:
    uint8_t damage;
    uint8_t range;
    uint8_t ammo_quantity;
    CowBoyBullet bala;

public:
    Weapon(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range,uint8_t ammo_quantity);
    bool isEmptyAmmo();
    CowBoyBullet shoot();

};

#endif //WEAPON_H
