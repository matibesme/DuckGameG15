#include "typemaker.h"
#include <utility>
TypeMaker::TypeMaker() {
  backgrounds_id.insert(std::pair<uint8_t, std::string>(0x00, ""));
  backgrounds_id.insert(std::pair<uint8_t, std::string>(0x90, "River"));
  backgrounds_id.insert(std::pair<uint8_t, std::string>(0x91, "Forest"));
  backgrounds_id.insert(std::pair<uint8_t, std::string>(0x92, "Cloudy night"));

  platforms_id.insert(std::pair<uint8_t, std::string>(0x77, "Donut"));
  platforms_id.insert(std::pair<uint8_t, std::string>(0x78, "Industrial"));
  platforms_id.insert(std::pair<uint8_t, std::string>(0x79, "Nature"));
  platforms_id.insert(std::pair<uint8_t, std::string>(0x80, "Space"));
  platforms_id.insert(std::pair<uint8_t, std::string>(0x81, "Underground"));
  platforms_id.insert(std::pair<uint8_t, std::string>(0x82, "Donut long"));
  platforms_id.insert(std::pair<uint8_t, std::string>(0x83, "Nature long"));

  walls_id.insert(std::pair<uint8_t, std::string>(0x85, "Donut"));
  walls_id.insert(std::pair<uint8_t, std::string>(0x87, "Underground"));
  walls_id.insert(std::pair<uint8_t, std::string>(0x86, "Nature"));

  weapons_id.insert(std::pair<uint8_t, std::string>(0x35, "ak47"));
  weapons_id.insert(std::pair<uint8_t, std::string>(0x41, "banana"));
  weapons_id.insert(std::pair<uint8_t, std::string>(0x34, "cowboyPistol"));
  weapons_id.insert(std::pair<uint8_t, std::string>(0x36, "duelingPistol"));
  weapons_id.insert(std::pair<uint8_t, std::string>(0x40, "grenade"));
  weapons_id.insert(std::pair<uint8_t, std::string>(0x43, "laserRifle"));
  weapons_id.insert(std::pair<uint8_t, std::string>(0x42, "pewPewLaser"));
  weapons_id.insert(std::pair<uint8_t, std::string>(0x38, "shotgun"));
  weapons_id.insert(std::pair<uint8_t, std::string>(0x39, "sniper"));
  weapons_id.insert(std::pair<uint8_t, std::string>(0x37, "magnum"));

  armours_id.insert(std::pair<uint8_t, std::string>(0x74, "chestplate"));
  armours_id.insert(std::pair<uint8_t, std::string>(0x76, "knightsHelmet"));
}

std::string TypeMaker::get_type_background(uint8_t background_id) {
  return backgrounds_id.at(background_id);
}

std::string TypeMaker::get_type_platform(uint8_t platform_id) {
  return platforms_id.at(platform_id);
}

std::string TypeMaker::get_type_weapon(uint8_t weapon_id) {
  return weapons_id.at(weapon_id);
}

std::string TypeMaker::get_type_armour(uint8_t armour_id) {
  return armours_id.at(armour_id);
}

std::string TypeMaker::get_type_wall(uint8_t wall_id) {
  return walls_id.at(wall_id);
}
