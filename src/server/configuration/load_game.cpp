#include "load_game.h"
#include <filesystem>
#include <iostream>
#include <random>
#include <vector>

LoadGameFile::LoadGameFile(
    FactoryWeapons &factory_weapons, std::list<DTOPlatform> &platforms,
    std::map<uint16_t, RespawnPoint> &respawn_weapon_points,
    std::map<uint16_t, Protection> &map_defense,
    std::map<uint16_t, Protection> &respawn_defense_points,
    uint16_t &id_defense, uint16_t &id_weapons, uint8_t &id_boxes,
    std::map<uint16_t, std::shared_ptr<Weapon>> &map_free_weapons,
    std::list<Boxes> &list_boxes,
    std::map<uint16_t, std::unique_ptr<Bullet>> &map_bullets,
    uint16_t &id_balas, std::map<uint8_t, DuckPlayer> &map_personajes,
    std::map<uint8_t, std::string> &map_id_clientes,
    std::vector<std::string> &list_colors, uint8_t &scene_id,
    std::map<uint8_t, uint8_t> &colors_assigned)
    : factory_weapons(factory_weapons), platforms(platforms),
      respawn_weapon_points(respawn_weapon_points), map_defense(map_defense),
      respawn_defense_points(respawn_defense_points), id_defense(id_defense),
      id_weapons(id_weapons), id_boxes(id_boxes),
      map_free_weapons(map_free_weapons), list_boxes(list_boxes),
      map_bullets(map_bullets), id_bullets(id_balas),
      map_personajes(map_personajes), map_id_clientes(map_id_clientes),
      list_colors(list_colors), scene_id(scene_id),
      colors_assigned(colors_assigned) {}

void LoadGameFile::loadGame() {
  const std::string directory_path = DATA_PATH "/maps";
  std::vector<std::string> files;
  for (const auto &entry :
       std::filesystem::directory_iterator(directory_path)) {
    if (entry.path().extension() == ".yaml") {
      files.push_back(entry.path().string());
    }
  }

  if (files.empty()) {
    throw std::runtime_error("No hay archivos de mapas en el directorio");
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, files.size() - 1);
  std::string random_map = files[dis(gen)];

  YAML::Node map = YAML::LoadFile(random_map);

  scene_id = map["background_type"].as<uint8_t>();

  POSICION_INICIAL_X = map["duck spawns"][0]["pos_x"].as<float>();
  POSICION_INICIAL_Y = map["duck spawns"][0]["pos_y"].as<float>();

  for (const auto &platform : map["plataforms"]) {
    DTOPlatform dto_platform = {
        platform["type"].as<uint8_t>(), platform["pos_x"].as<float>(),
        platform["pos_y"].as<float>(), platform["width"].as<float>(),
        platform["height"].as<float>()};
    platforms.push_back(dto_platform);
  }

  int i = 0;
  for (auto &id : map_id_clientes) {
    colors_assigned.emplace(id.first, i);
    map_personajes.emplace(id.first,
                           DuckPlayer(0, id.first, POSICION_INICIAL_X,
                                      POSICION_INICIAL_Y, list_colors[i++]));
  }

  for (const auto &wall : map["walls"]) {
    DTOPlatform dto_wall = {
        wall["type"].as<uint8_t>(), wall["pos_x"].as<float>(),
        wall["pos_y"].as<float>(), wall["width"].as<float>(),
        wall["height"].as<float>()};
    platforms.push_back(dto_wall);
  }

  for (const auto &weapon : map["weapon spawns"]) {
    RespawnPoint respawn_point = {weapon["pos_x"].as<float>(),
                                  weapon["pos_y"].as<float>(),
                                  weapon["type"].as<uint8_t>()};
    respawn_weapon_points.emplace(id_weapons, respawn_point);
    map_free_weapons.emplace(id_weapons++,
                             factory_weapons.createWeapon(respawn_point.type,
                                                          respawn_point.x_pos,
                                                          respawn_point.y_pos));
  }

  for (const auto &armour : map["armour spawns"]) {
    Protection protection_point = {armour["type"].as<uint8_t>(),
                                   armour["pos_x"].as<float>(),
                                   armour["pos_y"].as<float>()};
    respawn_defense_points.emplace(id_defense, protection_point);
    map_defense.emplace(id_defense++, protection_point);
  }

  for (const auto &box : map["box spawns"]) {
    list_boxes.emplace_back(
        Boxes(TYPE_BOX, id_boxes++, box["pos_x"].as<float>(),
              box["pos_y"].as<float>(), 100, map_free_weapons, map_defense,
              map_bullets, id_bullets, id_weapons, id_defense));
  }
}

void LoadGameFile::loadConfigurations() {
  YAML::Node config = YAML::LoadFile(CONFIG_PATH "/config.yaml");

  NECESARY_VICTORY_ROUNDS = config["necesary_victories"].as<uint8_t>();
  GAMES_PER_ROUND = config["games_per_round"].as<uint8_t>();
  LIFE = config["life"].as<int>();
  VELOCIDAD_INICIAL = config["jump_velocity"].as<float>();
  GRAVEDAD = config["gravity"].as<float>();
  // GRANADA
  DAMAGE_GRANADA = config["granade"]["damage"].as<int>();
  RANGE_GRANADA = config["granade"]["range"].as<int>();
  AMMO_GRANADA = config["granade"]["ammo"].as<int>();
  RECOIL_GRANADA = config["granade"]["recoil"].as<float>();
  RADIO_EXPLOTION_GRANADA = config["granade"]["radius_explosion"].as<float>();
  // BANANA
  DAMAGE_BANANA = config["banana"]["damage"].as<int>();
  RANGE_BANANA = config["banana"]["range"].as<int>();
  AMMO_BANANA = config["banana"]["ammo"].as<int>();
  RECOIL_BANANA = config["banana"]["recoil"].as<float>();
  // AK47
  DAMAGE_AK47 = config["ak47"]["damage"].as<int>();
  RANGE_AK47 = config["ak47"]["range"].as<int>();
  AMMO_AK47 = config["ak47"]["ammo"].as<int>();
  RECOIL_AK47 = config["ak47"]["recoil"].as<float>();
  AK47_SPREAD_INITIAL = config["ak47"]["spread_initial"].as<float>();
  // LASER RIFLE
  DAMAGE_LASER_RIFLE = config["laser_rifle"]["damage"].as<int>();
  RANGE_LASER_RIFLE = config["laser_rifle"]["range"].as<int>();
  AMMO_LASER_RIFLE = config["laser_rifle"]["ammo"].as<int>();
  RECOIL_LASER_RIFLE = config["laser_rifle"]["recoil"].as<float>();
  LASER_RIFLE_SPREAD = config["laser_rifle"]["spread"].as<float>();
  // PEW PEW LASER
  DAMAGE_PEW_PEW_LASER = config["pew_pew_laser"]["damage"].as<int>();
  RANGE_PEW_PEW_LASER = config["pew_pew_laser"]["range"].as<int>();
  AMMO_PEW_PEW_LASER = config["pew_pew_laser"]["ammo"].as<int>();
  RECOIL_PEW_PEW_LASER = config["pew_pew_laser"]["recoil"].as<float>();
  PEW_PEW_LASER_MAX_SPREAD = config["pew_pew_laser"]["max_spread"].as<float>();
  // ESCOPETA
  DAMAGE_ESCOPETA = config["escopeta"]["damage"].as<int>();
  RANGE_ESCOPETA = config["escopeta"]["range"].as<int>();
  AMMO_ESCOPETA = config["escopeta"]["ammo"].as<int>();
  RECOIL_ESCOPETA = config["escopeta"]["recoil"].as<float>();
  ESCOPETA_MAX_SPREAD = config["escopeta"]["max_spread"].as<float>();
  // SNIPER
  DAMAGE_SNIPER = config["sniper"]["damage"].as<int>();
  RANGE_SNIPER = config["sniper"]["range"].as<int>();
  AMMO_SNIPER = config["sniper"]["ammo"].as<int>();
  RECOIL_SNIPER = config["sniper"]["recoil"].as<float>();
  // COWBOY
  DAMAGE_COWBOY = config["cowboy"]["damage"].as<int>();
  RANGE_COWBOY = config["cowboy"]["range"].as<int>();
  AMMO_COWBOY = config["cowboy"]["ammo"].as<int>();
  RECOIL_COWBOY = config["cowboy"]["recoil"].as<float>();

  // PISTOLA DE DUELOS
  DAMAGE_PISTOLA_DUELOS = config["pistola_de_duelos"]["damage"].as<int>();
  RANGE_PISTOLA_DUELOS = config["pistola_de_duelos"]["range"].as<int>();
  AMMO_PISTOLA_DUELOS = config["pistola_de_duelos"]["ammo"].as<int>();
  RECOIL_PISTOLA_DUELOS = config["pistola_de_duelos"]["recoil"].as<float>();
  PISTOLA_DUELOS_SPREAD = config["pistola_de_duelos"]["spread"].as<float>();

  // MAGNUM
  DAMAGE_MAGNUM = config["magnum"]["damage"].as<int>();
  RANGE_MAGNUM = config["magnum"]["range"].as<int>();
  AMMO_MAGNUM = config["magnum"]["ammo"].as<int>();
  RECOIL_MAGNUM = config["magnum"]["recoil"].as<float>();
  MAGNUM_SPREAD = config["magnum"]["spread"].as<float>();
}
