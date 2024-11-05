#ifndef ID_MAKER_H
#define ID_MAKER_H

#include <map>
#include <iostream>
#include <string>
#include <cstdint>

class IDMaker{

private:
    std::map<std::string, uint8_t> backgrounds_id;
    std::map<std::string, uint8_t> platforms_id;
    std::map<std::string, uint8_t> weapons_id;
    std::map<std::string, uint8_t> armours_id;
    std::map<std::string, uint8_t> walls_id;

public:
    IDMaker();
    uint8_t get_id_background(std::string background_name);
    uint8_t get_id_platform(std::string platform_name);
    uint8_t get_id_weapon(std::string weapon_name);
    uint8_t get_id_armour(std::string armour_name);
    uint8_t get_id_wall(std::string wall_name);
};

#endif