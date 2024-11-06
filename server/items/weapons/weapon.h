#ifndef WEAPON_H
#define WEAPON_H
#include "../objeto.h"
#include <cstdint>
#include <list>
#include "../bullets/bullet.h"
#include "../common/common_constant.h"
#include <memory>

class Weapon : public Objeto {
protected:
    uint8_t damage;
    uint8_t range;
    uint8_t ammo_quantity;
    float recoil;
    int reload_time;
    int bullet_count;

public:
    Weapon(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range,uint8_t ammo_quantity,float recoil);

    virtual bool isEmptyAmmo() = 0;
    virtual std::unique_ptr<Bullet> shoot() = 0;
    virtual bool isActive() = 0;

    virtual void setReloadTime(int reload_time_) = 0;
    virtual int getReloadTime() = 0;

    virtual void stopShooting() = 0;
};

#endif //WEAPON_H
