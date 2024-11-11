#ifndef TYPE_MAKER_H
#define TYPE_MAKER_H

#include <map>
#include <iostream>
#include <string>
#include <cstdint>

class TypeMaker{

private:
    std::map<uint8_t, std::string> backgrounds_id;
    std::map<uint8_t, std::string> platforms_id;
    std::map<uint8_t, std::string> weapons_id;
    std::map<uint8_t, std::string> armours_id;
    std::map<uint8_t, std::string> walls_id;

public:
    TypeMaker();
    std::string get_type_background(uint8_t background_id);
    std::string get_type_platform(uint8_t platform_id);
    std::string get_type_weapon(uint8_t weapon_id);
    std::string get_type_armour(uint8_t armour_id);
    std::string get_type_wall(uint8_t wall_id);
};

#endif