#include "load_game.h"
#include <iostream>
#include <filesystem>
#include <vector>
#include <random>

LoadGameFile::LoadGameFile(FactoryWeapons& factory_weapons,std::list<DTOPlatform> &platforms, std::list<RespawnPoint>& respawn_weapon_points,std::map<uint16_t, Protection>& map_helmet,std::map<uint16_t, Protection>& map_armor,uint16_t& id_weapons, uint16_t& id_helemets,
    uint16_t& id_armors, uint8_t& id_boxes,std::map<uint16_t, std::shared_ptr<Weapon>>& map_free_weapons, std::list<Boxes>& list_boxes,
    std::map<uint16_t, std::unique_ptr<Bullet>>& map_bullets, uint16_t& id_balas):
    factory_weapons(factory_weapons), platforms(platforms), respawn_weapon_points(respawn_weapon_points), map_helmet(map_helmet), map_armor(map_armor),
    id_weapons(id_weapons), id_helemets(id_helemets), id_armors(id_armors), id_boxes(id_boxes) , map_free_weapons(map_free_weapons), list_boxes(list_boxes) , map_bullets(map_bullets), id_bullets(id_balas) {}

void LoadGameFile::loadGame() {
    
    

    const std::string directory_path = "../data/maps";
    std::vector<std::string> files;
    for (const auto & entry : std::filesystem::directory_iterator(directory_path)) {
        if (entry.path().extension() == ".yaml"){
        files.push_back(entry.path().string());
        }
    }

    if (files.empty()){
        throw std::runtime_error("No hay archivos de mapas en el directorio");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, files.size()-1);
    std::string random_map = files[dis(gen)];

    YAML::Node map = YAML::LoadFile(random_map);

    SCENE_ID=map["background_type"].as<uint8_t>();

    POSICION_INICIAL_X=map["duck spawns"][0]["pos_x"].as<float>();
    POSICION_INICIAL_Y=map["duck spawns"][0]["pos_y"].as<float>();


    for (const auto& platform : map["plataforms"]) {

        DTOPlatform dto_platform={platform["type"].as<uint8_t>(),platform["pos_x"].as<float>(),platform["pos_y"].as<float>(),platform["width"].as<float>(),platform["height"].as<float>()};
        platforms.push_back(dto_platform);
    }

    for (const auto& wall : map["walls"]) {

        DTOPlatform dto_wall={wall["type"].as<uint8_t>(),wall["pos_x"].as<float>(),wall["pos_y"].as<float>(),wall["width"].as<float>(),wall["height"].as<float>()};
        platforms.push_back(dto_wall);
    }

    for (const auto& weapon : map["weapon spawns"]) {
        RespawnPoint respawn_point={weapon["pos_x"].as<float>(),weapon["pos_y"].as<float>(),weapon["type"].as<uint8_t>()};
        respawn_weapon_points.push_back(respawn_point);
        map_free_weapons.emplace(id_weapons++, factory_weapons.createWeapon(respawn_point.type, respawn_point.x_pos, respawn_point.y_pos));
    }

    for (const auto& armour : map["armour spawns"]) {
      Protection protection_point={armour["type"].as<uint8_t>(),armour["pos_x"].as<float>(),armour["pos_y"].as<float>()};
      if (protection_point.type == HELMET_EQUIPPED) {
        map_helmet.emplace(id_helemets++, protection_point);
      } else{
        map_armor.emplace(id_armors++, protection_point);
      }
    }

    for (const auto& box : map["box spawns"])
    {
        list_boxes.emplace_back(Boxes(TYPE_BOX,id_boxes++, box["pos_x"].as<float>(), box["pos_y"].as<float>(), 100, map_free_weapons, map_armor, map_helmet, map_bullets, id_bullets, id_weapons, id_helemets, id_armors));
    }


}