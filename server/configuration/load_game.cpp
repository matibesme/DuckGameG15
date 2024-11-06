#include "load_game.h"
#include <iostream>

LoadGameFile::LoadGameFile() {}

void LoadGameFile::loadGame(std::list<DTOPlatform> &platforms, std::list<std::pair<float,float>>& respawn_weapon_points) {
    
    YAML::Node map = YAML::LoadFile("../data/maps/mapaa.yaml");
    SCENE_ID=map["background_type"].as<uint8_t>();

    POSICION_INICIAL_X=map["duck spawns"][0]["pos_x"].as<float>();
    POSICION_INICIAL_Y=map["duck spawns"][0]["pos_y"].as<float>();

    RESPAWN_WEAPON_X=map["weapon spawns"][0]["pos_x"].as<float>();
    RESPAWN_WEAPON_Y=map["weapon spawns"][0]["pos_y"].as<float>();

    for (const auto& platform : map["plataforms"]) {

        DTOPlatform dto_platform={platform["type"].as<uint8_t>(),platform["pos_x"].as<float>(),platform["pos_y"].as<float>(),platform["width"].as<float>(),platform["height"].as<float>()};
        platforms.push_back(dto_platform);
    }

    for (const auto& wall : map["walls"]) {

        DTOPlatform dto_wall={wall["type"].as<uint8_t>(),wall["pos_x"].as<float>(),wall["pos_y"].as<float>(),wall["width"].as<float>(),wall["height"].as<float>()};
        platforms.push_back(dto_wall);
    }

    for (const auto& weapon : map["weapon spawns"]) {
        std::pair<float,float> weapon_point={weapon["pos_x"].as<float>(),weapon["pos_y"].as<float>()};
        respawn_weapon_points.push_back(weapon_point);
    }

}