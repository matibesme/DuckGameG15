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
    std::map<uint16_t, RespawnPoint>& respawn_weapon_points;
    std::map<uint16_t, Protection>& map_defense;
    std::map<uint16_t,Protection>& respawn_defense_points;
    uint16_t& id_defense;
    uint16_t& id_weapons;
    uint8_t& id_boxes;
    std::map<uint16_t, std::shared_ptr<Weapon>>& map_free_weapons;
    std::list<Boxes>& list_boxes;
    std::map<uint16_t, std::unique_ptr<Bullet>>& map_bullets;
    uint16_t& id_bullets;

public:
    LoadGameFile(FactoryWeapons& factory_weapons,std::list<DTOPlatform> &platforms, std::map<uint16_t, RespawnPoint>& respawn_weapon_points,
        std::map<uint16_t,Protection>& map_defense,std::map<uint16_t,Protection>& respawn_defense_points,uint16_t& id_defense,
        uint16_t& id_weapons,uint8_t& id_boxes,std::map<uint16_t, std::shared_ptr<Weapon>>& map_free_weapons, std::list<Boxes>& list_boxes,
        std::map<uint16_t, std::unique_ptr<Bullet>>& map_bullets, uint16_t& id_bullets);
    void loadGame();
};
