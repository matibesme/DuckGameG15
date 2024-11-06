//
// Created by matibesme on 5/11/24.
//

#include "factory_weapons.h"


FactoryWeapons::FactoryWeapons() {}

std::shared_ptr<Weapon> FactoryWeapons::createWeapon(uint8_t type, float x, float y) {
    switch (type) {
      /*  case AK47_GUN:
            return std::make_shared<AK47>(AK47_GUN, 1, x, y, 10, 10, 10, 10);
        case PISTOLA_DUELOS_GUN:
            return std::make_shared<DuelPistol>(PISTOLA_DUELOS_GUN, 1, x, y, 10, 10, 10, 10);
        case MAGNUM_GUN:
            return std::make_shared<Magnum>(MAGNUM_GUN, 1, x, y, 10, 10, 10, 10);
        case ESCOPETA_GUN:
            return std::make_shared<Shotgun>(ESCOPETA_GUN, 1, x, y, 10, 10, 10, 10);
        case SNIPER_GUN:
            return std::make_shared<Sniper>(SNIPER_GUN, 1, x, y, 10, 10, 10, 10);*/
        case GRANADA_GUN:
            return std::make_shared<Granada>(GRANADA_GUN, 1, x, y, 10, 10, 10, 10);
        case BANANA_GUN:
            return std::make_shared<Banana>(BANANA_GUN, 1, x, y, 10, 10, 10, 10);
      /*  case PEW_PEW_LASER_GUN:
            return std::make_shared<PewPewLaser>(PEW_PEW_LASER_GUN, 1, x, y, 10, 10, 10, 10);
        case LASER_RIFLE_GUN:
            return std::make_shared<LaserRifle>(LASER_RIFLE_GUN, 1, x, y, 10, 10, 10, 10);*/
        default:
            return nullptr;
    }
}