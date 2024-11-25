#ifndef PATH_MAKER_H
#define PATH_MAKER_H

#include <string>

class PathMaker {
public:
  PathMaker();
  std::string get_platform_path(const std::string &platform_type);
  std::string get_background_path(const std::string &background_type);
  std::string get_weapon_path(const std::string &weapon_type);
  std::string get_armour_path(const std::string &armour_type);
  std::string get_wall_path(const std::string &wall_type);
};

#endif
