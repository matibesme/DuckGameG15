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
    std::map<uint8_t, std::string> &map_id_clientes)
    : factory_weapons(factory_weapons), platforms(platforms),
      respawn_weapon_points(respawn_weapon_points), map_defense(map_defense),
      respawn_defense_points(respawn_defense_points), id_defense(id_defense),
      id_weapons(id_weapons), id_boxes(id_boxes),
      map_free_weapons(map_free_weapons), list_boxes(list_boxes),
      map_bullets(map_bullets), id_bullets(id_balas),
      map_personajes(map_personajes), map_id_clientes(map_id_clientes),
      list_colors({"red", "blue", "green", "yellow", "pink", "purple", "orange",
                   "brown", "black", "white"}) {}

void LoadGameFile::loadGame() {

  const std::string directory_path = "../data/maps";
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

  SCENE_ID = map["background_type"].as<uint8_t>();

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
  YAML::Node config = YAML::LoadFile("../server/configuration/config.yaml");

  GRAVEDAD = config["gravity"].as<float>();
  VELOCIDAD_INICIAL = config["initial_speed"].as<float>();
  GRAVITY_FLAP = config["gravity_flap"].as<float>();
  CANT_FLAP = config["flap_quantity"].as<uint8_t>();
  LIFE = config["life"].as<uint8_t>();



  //GRANADA
  DAMAGE_GRANADA = config["granade"]["damage"].as<uint8_t>();
  RANGE_GRANADA = config["granade"]["range"].as<uint8_t>();
  AMMO_GRANADA = config["granade"]["ammo"].as<uint8_t>();
  RECOIL_GRANADA = config["granade"]["recoil"].as<float>();
  //BANANA
  DAMAGE_BANANA = config["banana"]["damage"].as<uint8_t>();
  RANGE_BANANA = config["banana"]["range"].as<uint8_t>();
  AMMO_BANANA = config["banana"]["ammo"].as<uint8_t>();
  RECOIL_BANANA = config["banana"]["recoil"].as<float>();
  //AK47
  DAMAGE_AK47 = config["ak47"]["damage"].as<uint8_t>();
  RANGE_AK47 = config["ak47"]["range"].as<uint8_t>();
  AMMO_AK47 = config["ak47"]["ammo"].as<uint8_t>();
  RECOIL_AK47 = config["ak47"]["recoil"].as<float>();
  //LASER RIFLE
  DAMAGE_LASER_RIFLE = config["laser_rifle"]["damage"].as<uint8_t>();
  RANGE_LASER_RIFLE = config["laser_rifle"]["range"].as<uint8_t>();
  AMMO_LASER_RIFLE = config["laser_rifle"]["ammo"].as<uint8_t>();
  RECOIL_LASER_RIFLE = config["laser_rifle"]["recoil"].as<float>();
  //PEW PEW LASER
  DAMAGE_PEW_PEW_LASER = config["pew_pew_laser"]["damage"].as<uint8_t>();
  RANGE_PEW_PEW_LASER = config["pew_pew_laser"]["range"].as<uint8_t>();
  AMMO_PEW_PEW_LASER = config["pew_pew_laser"]["ammo"].as<uint8_t>();
  RECOIL_PEW_PEW_LASER = config["pew_pew_laser"]["recoil"].as<float>();
  //ESCOPETA
  DAMAGE_ESCOPETA = config["escopeta"]["damage"].as<uint8_t>();
  RANGE_ESCOPETA = config["escopeta"]["range"].as<uint8_t>();
  AMMO_ESCOPETA = config["escopeta"]["ammo"].as<uint8_t>();
  RECOIL_ESCOPETA = config["escopeta"]["recoil"].as<float>();
  //SNIPER
  DAMAGE_SNIPER = config["sniper"]["damage"].as<uint8_t>();
  RANGE_SNIPER = config["sniper"]["range"].as<uint8_t>();
  AMMO_SNIPER = config["sniper"]["ammo"].as<uint8_t>();
  RECOIL_SNIPER = config["sniper"]["recoil"].as<float>();
  //COWBOY
  DAMAGE_COWBOY = config["cowboy"]["damage"].as<uint8_t>();
  RANGE_COWBOY = config["cowboy"]["range"].as<uint8_t>();
  AMMO_COWBOY = config["cowboy"]["ammo"].as<uint8_t>();
  RECOIL_COWBOY = config["cowboy"]["recoil"].as<float>();

  //PISTOLA DE DUELOS
  DAMAGE_PISTOLA_DUELOS = config["pistola_de_duelos"]["damage"].as<uint8_t>();
  RANGE_PISTOLA_DUELOS = config["pistola_de_duelos"]["range"].as<uint8_t>();
  AMMO_PISTOLA_DUELOS = config["pistola_de_duelos"]["ammo"].as<uint8_t>();
  RECOIL_PISTOLA_DUELOS = config["pistola_de_duelos"]["recoil"].as<float>();

  //MAGNUM
  DAMAGE_MAGNUM = config["magnum"]["damage"].as<uint8_t>();
  RANGE_MAGNUM = config["magnum"]["range"].as<uint8_t>();
  AMMO_MAGNUM = config["magnum"]["ammo"].as<uint8_t>();
  RECOIL_MAGNUM = config["magnum"]["recoil"].as<float>();
}
