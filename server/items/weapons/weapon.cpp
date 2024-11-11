
#include "weapon.h"

Weapon::Weapon(uint8_t type, uint8_t id, float x_pos, float y_pos,
               uint8_t damage, uint8_t range, uint8_t ammo_quantity,
               float recoil)
    : Objeto(type, id, x_pos, y_pos), damage(damage), range(range),
      ammo_quantity(ammo_quantity), recoil(recoil), reload_time(0),
      bullet_count(0) {}
