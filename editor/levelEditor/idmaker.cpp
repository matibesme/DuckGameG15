#include "idmaker.h"

#include <utility>

IDMaker::IDMaker(){
    backgrounds_id.insert(std::pair<std::string, uint8_t>("City", 0x90));
    backgrounds_id.insert(std::pair<std::string, uint8_t>("Forest", 0x91));

    platforms_id.insert(std::pair<std::string, uint8_t>("Donut", 0x77));
    platforms_id.insert(std::pair<std::string, uint8_t>("Industrial", 0x78));
    platforms_id.insert(std::pair<std::string, uint8_t>("Nature", 0x79));
    platforms_id.insert(std::pair<std::string, uint8_t>("Space", 0x80));
    platforms_id.insert(std::pair<std::string, uint8_t>("Underground", 0x81));

    weapons_id.insert(std::pair<std::string, uint8_t>("ak47", 0x35));
    weapons_id.insert(std::pair<std::string, uint8_t>("banana", 0x41));
    weapons_id.insert(std::pair<std::string, uint8_t>("cowboyPistol", 0x34));
    weapons_id.insert(std::pair<std::string, uint8_t>("duelingPistol", 0x36));
    weapons_id.insert(std::pair<std::string, uint8_t>("grenade", 0x40));
    weapons_id.insert(std::pair<std::string, uint8_t>("laserRifle", 0x43));
    weapons_id.insert(std::pair<std::string, uint8_t>("pewPewLaser", 0x42));
    weapons_id.insert(std::pair<std::string, uint8_t>("shotgun", 0x38));
    weapons_id.insert(std::pair<std::string, uint8_t>("sniper", 0x39));
    weapons_id.insert(std::pair<std::string, uint8_t>("magnum", 0x37));

    armours_id.insert(std::pair<std::string, uint8_t>("chestplate", 0x74));
    armours_id.insert(std::pair<std::string, uint8_t>("knightsHelmet", 0x76));
}

uint8_t IDMaker::get_id_background(std::string background_name){
    return backgrounds_id.at(background_name);
}

uint8_t IDMaker::get_id_platform(std::string platform_name){
    return platforms_id.at(platform_name);
}

uint8_t IDMaker::get_id_weapon(std::string weapon_name){
    return weapons_id.at(weapon_name);
}

uint8_t IDMaker::get_id_armour(std::string armour_name){
    return armours_id.at(armour_name);
}
