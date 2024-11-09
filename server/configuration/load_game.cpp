#include "load_game.h"
#include <iostream>
#include <filesystem>
#include <vector>
#include <random>

LoadGameFile::LoadGameFile() {}

void LoadGameFile::loadGame(std::list<DTOPlatform> &platforms, std::list<RespawnPoint>& respawn_weapon_points) {
    
    

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
        RespawnPoint respawn_point={weapon["pos_x"].as<float>(),weapon["pos_y"].as<float>(),weapon["type"].as<uint8_t>()};
        respawn_weapon_points.push_back(respawn_point);
    }

}