#include "pathmaker.h"

// static const char* DATA_RELATIVE_PATH = "data";
static const char *PLATFORMS_RELATIVE_PATH = "/platforms/";
static const char *BACKGROUNDS_RELATIVE_PATH = "/backgrounds/";
static const char *WEAPONS_RELATIVE_PATH = "/weapons/";
static const char *ARMOURS_RELATIVE_PATH = "/armour/";
static const char *WALLS_RELATIVE_PATH = "/walls/";
static const char *EXTENSION = ".png";

#include <iostream>
PathMaker::PathMaker() {}
std::string PathMaker::get_platform_path(std::string platform_type) {
  std::string path = std::string(DATA_PATH) +
                     std::string(PLATFORMS_RELATIVE_PATH) + platform_type +
                     std::string(EXTENSION);
  return path;
}

std::string PathMaker::get_background_path(std::string background_type) {
  std::string path = std::string(DATA_PATH) +
                     std::string(BACKGROUNDS_RELATIVE_PATH) + background_type +
                     std::string(EXTENSION);

  return path;
}

std::string PathMaker::get_weapon_path(std::string weapon_type) {
  std::string path = std::string(DATA_PATH) +
                     std::string(WEAPONS_RELATIVE_PATH) + weapon_type +
                     std::string(EXTENSION);

  return path;
}

std::string PathMaker::get_armour_path(std::string armour_type) {
  std::string path = std::string(DATA_PATH) +
                     std::string(ARMOURS_RELATIVE_PATH) + armour_type +
                     std::string(EXTENSION);
  return path;
}

std::string PathMaker::get_wall_path(std::string wall_type) {
  std::string path = std::string(DATA_PATH) + std::string(WALLS_RELATIVE_PATH) +
                     wall_type + std::string(EXTENSION);
  return path;
}
