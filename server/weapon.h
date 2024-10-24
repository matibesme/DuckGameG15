
#ifndef WEAPON_H
#define WEAPON_H
#include <cstdint>
#include <list>

#include  "objeto.h"
#include "bullet.h"


class Weapon : public Objeto {
private:
    uint8_t damage;
    uint8_t range;
    uint8_t ammo;
    uint8_t id;
    std::list<Bullet> ammo_list;

public:
    Weapon(uint8_t damage, uint8_t range, uint8_t ammo);
    uint8_t getAmmo();
    void setAmmo(uint8_t ammo);
    void shoot();
    void setId(uint8_t id);
    uint8_t getId();
};



#endif //WEAPON_H
