#ifndef ID_MAKER_H
#define ID_MAKER_H

#include <cstdint>
#include <iostream>
#include <map>
#include <string>

class IDMaker {

private:
    std::map<std::string, int> backgrounds_id;
    std::map<std::string, int> platforms_id;
    std::map<std::string, int> weapons_id;
    std::map<std::string, int> armours_id;
    std::map<std::string, int> walls_id;

public:
    IDMaker();
    int get_id_background(std::string background_name);
    int get_id_platform(std::string platform_name);
    int get_id_weapon(std::string weapon_name);
    int get_id_armour(std::string armour_name);
    int get_id_wall(std::string wall_name);
};

#endif