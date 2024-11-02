#ifndef PATH_MAKER_H
#define PATH_MAKER_H

#include <string>

class PathMaker{

public:
    PathMaker();
    std::string get_platform_path(std::string platform_type);
    std::string get_background_path(std::string background_type);
    std::string get_weapon_path(std::string weapon_type);
    std::string get_armour_path(std::string armour_type);
};

#endif