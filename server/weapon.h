
#ifndef WEAPON_H
#define WEAPON_H
#include <cstdint>
#include <list>

#include  "objeto.h"
#include "bullet.h"
#include "constant_definitons.h"

class Weapon : public Objeto {
private:
    uint8_t damage;
    uint8_t range;

    std::list<Bullet> ammo_list;

public:
    Weapon(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range);
    uint8_t getAmmo();
    void setAmmo(uint8_t ammo);
    bool Weapon::isEmptyAmmo();
    Bullet& shoot();
    void setId(uint8_t id);
    uint8_t getId();
};



#endif //WEAPON_H
