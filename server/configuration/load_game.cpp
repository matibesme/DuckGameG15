#include "load_game.h"


LoadGameFile::LoadGameFile() {}

void LoadGameFile::loadGame(std::list<DTOPlatform> &platforms) {
    
    YAML::Node map = YAML::LoadFile("../server/configuration/map.yaml");

    S_POSICION_INICIAL_X= map["duck"][0]["x"].as<float>();
    S_POSICION_INICIAL_Y= map["duck"][0]["y"].as<float>();
    S_LIFE= map["duck"][0]["life"].as<uint8_t>();
    S_RESPAWN_WEAPON_X= map["respawn_weapons_point"][0]["x"].as<float>();
    S_RESPAWN_WEAPON_Y= map["respawn_weapons_point"][0]["y"].as<float>();


    for (const auto& platform : map["platforms"]) {
        platforms.emplace_back(DTOPlatform{platform["type"].as<uint8_t>(),
                                                  platform["x"].as<float>(), platform["y"].as<float>(),
                                                  platform["width"].as<float>(), platform["height"].as<float>()});
    }

}