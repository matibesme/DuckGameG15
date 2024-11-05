#include "load_game.h"
#include <iostream>

LoadGameFile::LoadGameFile() {}

void LoadGameFile::loadGame(std::list<DTOPlatform> &platforms, std::list<DTOPlatform> &walls) {
    
    YAML::Node map = YAML::LoadFile("../data/maps/mapa_prueba.yaml");
    SCENE_ID=map["background_type"].as<uint8_t>();

    POSICION_INICIAL_X=map["duck spawns"][0]["pos_x"].as<float>();
    POSICION_INICIAL_Y=map["duck spawns"][0]["pos_y"].as<float>();
    std::cout << POSICION_INICIAL_X << std::endl;
    std::cout << POSICION_INICIAL_Y << std::endl;

    for (const auto& platform : map["plataforms"]) {
        std::string type_str = platform["type"].as<std::string>();
        uint8_t type_value = static_cast<uint8_t>(type_str[0]);
        DTOPlatform dto_platform={type_value,platform["pos_x"].as<float>(),platform["pos_y"].as<float>(),platform["width"].as<float>(),platform["height"].as<float>()};
        platforms.push_back(dto_platform);
    }

    for (const auto& wall : map["walls"]) {
        std::string type_str = wall["type"].as<std::string>();
        uint8_t type_value = static_cast<uint8_t>(type_str[0]);
        DTOPlatform dto_wall={type_value,wall["pos_x"].as<float>(),wall["pos_y"].as<float>(),wall["width"].as<float>(),wall["height"].as<float>()};
        walls.push_back(dto_wall);
    }

}