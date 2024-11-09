//
// Created by matibesme on 5/11/24.
//

#include "factory_weapons.h"
#include "banana.h"
#include "granada.h"
#include "ak47.h"
#include "laser_rifle.h"
#include "pewpew_laser.h"
#include "shotgun.h"
#include "sniper.h"
#include "cowboy_pistol.h"
#include "duel_pistol.h"
#include "magnum.h"
#include "common_constant.h"



FactoryWeapons::FactoryWeapons() {}

std::shared_ptr<Weapon> FactoryWeapons::createWeapon(uint8_t type, float x, float y) {
    switch (type) {

        case GRANADA_GUN:
            return std::make_shared<Granada>(GRANADA_GUN, 1, x, y, 10, 38, 100, 0);
        case BANANA_GUN:
            return std::make_shared<Banana>(BANANA_GUN, 1, x, y, 10, 10, 100, 0);
        case AK47_GUN:
            return std::make_shared<Ak47>(AK47_GUN, 1, x, y, 10, 13, 300, 1);
        case LASER_RIFLE_GUN:
            return std::make_shared<LaserRifle>(LASER_RIFLE_GUN, 1, x, y, 10, 30, 100, 0);
        case PEW_PEW_LASER_GUN:
            return std::make_shared<PewPewLaser>(PEW_PEW_LASER_GUN, 1, x, y, 10, 38, 120, 0);
        case ESCOPETA_GUN:
            return std::make_shared<Shotgun>(ESCOPETA_GUN, 1, x, y, 10, 9, 200, 0);
        case SNIPER_GUN:
            return std::make_shared<Sniper>(SNIPER_GUN, 1, x, y, 10, 64, 300, 0);
        case COWBOY_GUN:
            return std::make_shared<CowboyPistol>(COWBOY_GUN, 1, x, y, 10, 20, 600, 0);
        case PISTOLA_DUELOS_GUN:
            return std::make_shared<DuelPistol>(PISTOLA_DUELOS_GUN, 1, x, y, 10, 5, 100, 0);
        case MAGNUM_GUN:
            return std::make_shared<Magnum>(MAGNUM_GUN, 1, x, y, 10, 20, 600, 2);

        default:
            return nullptr;
    }
}
