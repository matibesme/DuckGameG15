#pragma once
#include <list>
#include "../common/common_constant.h"
#include "../../common/dto_definitions.h"
#include "../items/ducks/duck.h"
#include "../items/weapons/weapon.h"
#include <yaml-cpp/yaml.h>

#include "items/boxes.h"
#include "items/weapons/factory_weapons.h"


class LoadGameFile
{
private:
    FactoryWeapons& factory_weapons;
    std::list<DTOPlatform> &platforms;
    std::list<RespawnPoint>& respawn_weapon_points;
    std::map<uint16_t, Protection>& map_helmet;
    std::map<uint16_t, Protection>& map_armor;
    uint16_t& id_weapons;
    uint16_t& id_helemets;
    uint16_t& id_armors;
    uint8_t& id_boxes;
    std::map<uint16_t, std::shared_ptr<Weapon>>& map_free_weapons;
    std::list<Boxes>& list_boxes;
    std::map<uint16_t, std::unique_ptr<Bullet>>& map_bullets;
    uint16_t& id_bullets;

public:
    LoadGameFile(FactoryWeapons& factory_weapons,std::list<DTOPlatform> &platforms, std::list<RespawnPoint>& respawn_weapon_points,std::map<uint16_t,
        Protection>& map_helmet,std::map<uint16_t, Protection>& map_armor,uint16_t& id_weapons, uint16_t& id_helemets, uint16_t& id_armors,
        uint8_t& id_boxes,std::map<uint16_t, std::shared_ptr<Weapon>>& map_free_weapons, std::list<Boxes>& list_boxes,
        std::map<uint16_t, std::unique_ptr<Bullet>>& map_bullets, uint16_t& id_bullets);
    void loadGame();
};
