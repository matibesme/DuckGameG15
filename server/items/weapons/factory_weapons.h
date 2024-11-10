//
// Created by matibesme on 5/11/24.
//

#ifndef FACTORY_WEAPONS_H
#define FACTORY_WEAPONS_H
#include "banana.h"
#include "cowboy_pistol.h"
#include "duel_pistol.h"
#include "magnum.h"
#include "granada.h"


class FactoryWeapons {

public:
    FactoryWeapons();
    std::shared_ptr<Weapon> createWeapon(uint8_t type, float x_pos, float y_pos);
    std::shared_ptr<Weapon> generateRandomWeapon(float pos_x, float pos_y);

};



#endif //FACTORY_WEAPONS_H
