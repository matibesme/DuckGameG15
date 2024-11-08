#pragma once
//
// Created by matibesme on 31/10/24.
//

#ifndef DUCK_ACTION_H
#define DUCK_ACTION_H
#include <map>
#include <memory>
#include <items/ducks/duck.h>
#include <items/weapons/weapon.h>
#include <items/bullets/bullet.h>
#include "server_constant.h"



class DuckAction {
    private:
        std::map<uint8_t, DuckPlayer>& map_personajes;
        std::map<uint16_t,std::shared_ptr<Weapon>>& map_free_weapons;
        std::map<uint16_t, std::unique_ptr<Bullet>>& map_bullets;
        uint16_t& id_balas;
        uint16_t& id_weapons;
    public:
    DuckAction(std::map<uint8_t, DuckPlayer>& map_personajes,
                 std::map<uint16_t,std::shared_ptr<Weapon>>& map_free_weapons,
                 std::map<uint16_t, std::unique_ptr<Bullet>>& map_bullets,
                 uint16_t& id_balas, uint16_t& id_weapons);
    void movementComand(uint8_t comando);
    void weaponComand(uint8_t comando);

};



#endif //DUCK_ACTION_H
