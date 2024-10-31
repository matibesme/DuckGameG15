#ifndef WEAPON_H
#define WEAPON_H
#include "../objeto.h"
#include <cstdint>
#include <list>
#include "../bullets/bullet.h"
#include "../../constant_definitons.h"
#include <memory>

class Weapon : public Objeto {
protected:
    uint8_t damage;
    uint8_t range;
    uint8_t ammo_quantity;
    float recoil;

public:
    Weapon(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range,uint8_t ammo_quantity,float recoil);

    virtual bool isEmptyAmmo() = 0;
    virtual std::unique_ptr<Bullet> shoot() = 0;
    virtual bool isActive() = 0;

};

#endif //WEAPON_H
