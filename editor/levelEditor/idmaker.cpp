#include "idmaker.h"

#include <utility>

IDMaker::IDMaker(){
    backgrounds_id.insert(std::pair<std::string, int>("", 0x00));
    backgrounds_id.insert(std::pair<std::string, int>("City", 0x90));
    backgrounds_id.insert(std::pair<std::string, int>("Forest", 0x91));
    backgrounds_id.insert(std::pair<std::string, int>("Cloudy night", 0x92));

    platforms_id.insert(std::pair<std::string, int>("Donut", 0x77));
    platforms_id.insert(std::pair<std::string, int>("Industrial", 0x78));
    platforms_id.insert(std::pair<std::string, int>("Nature", 0x79));
    platforms_id.insert(std::pair<std::string, int>("Space", 0x80));
    platforms_id.insert(std::pair<std::string, int>("Underground", 0x81));
    platforms_id.insert(std::pair<std::string, int>("Donut long", 0x82));
    platforms_id.insert(std::pair<std::string, int>("Nature long", 0x83));

    walls_id.insert(std::pair<std::string, int>("Donut", 0x85));
    walls_id.insert(std::pair<std::string, int>("Underground", 0x86));
    walls_id.insert(std::pair<std::string, int>("Nature", 0x87));

    weapons_id.insert(std::pair<std::string, int>("ak47", 0x35));
    weapons_id.insert(std::pair<std::string, int>("banana", 0x41));
    weapons_id.insert(std::pair<std::string, int>("cowboyPistol", 0x34));
    weapons_id.insert(std::pair<std::string, int>("duelingPistol", 0x36));
    weapons_id.insert(std::pair<std::string, int>("grenade", 0x40));
    weapons_id.insert(std::pair<std::string, int>("laserRifle", 0x43));
    weapons_id.insert(std::pair<std::string, int>("pewPewLaser", 0x42));
    weapons_id.insert(std::pair<std::string, int>("shotgun", 0x38));
    weapons_id.insert(std::pair<std::string, int>("sniper", 0x39));
    weapons_id.insert(std::pair<std::string, int>("magnum", 0x37));

    armours_id.insert(std::pair<std::string, int>("chestplate", 0x74));
    armours_id.insert(std::pair<std::string, int>("knightsHelmet", 0x76));
}

int IDMaker::get_id_background(std::string background_name){
    return backgrounds_id.at(background_name);
}

int IDMaker::get_id_platform(std::string platform_name){
    return platforms_id.at(platform_name);
}

int IDMaker::get_id_weapon(std::string weapon_name){
    return weapons_id.at(weapon_name);
}

int IDMaker::get_id_armour(std::string armour_name){
    return armours_id.at(armour_name);
}

int IDMaker::get_id_wall(std::string wall_name){
    return walls_id.at(wall_name);
}
