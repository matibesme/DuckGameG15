#pragma once
//
// Created by matibesme on 31/10/24.
//

#ifndef DUCK_ACTION_H
#define DUCK_ACTION_H
#include "dto_definitions.h"
#include "server_constant.h"
#include <items/bullets/bullet.h>
#include <items/ducks/duck.h>
#include <items/weapons/weapon.h>
#include <map>
#include <memory>

class DuckAction {
private:
  std::map<uint8_t, DuckPlayer> &map_personajes;
  std::map<uint16_t, std::shared_ptr<Weapon>> &map_free_weapons;
  std::map<uint16_t, RespawnPoint> &respawn_weapon_points;
  std::map<uint16_t, uint8_t> &time_weapon_last_respawn;
  std::map<uint16_t, std::unique_ptr<Bullet>> &map_bullets;
  std::map<uint16_t, Protection> &map_defense;
  std::map<uint16_t, Protection> &respawn_defense_points;
  std::map<uint16_t, uint8_t> &time_defense_last_respawn;
  uint16_t &id_defense;
  uint16_t &id_balas;
  uint16_t &id_weapons;

public:
  DuckAction(std::map<uint8_t, DuckPlayer> &map_personajes,
             std::map<uint16_t, std::shared_ptr<Weapon>> &map_free_weapons,
             std::map<uint16_t, RespawnPoint> &respawn_weapon_points,
             std::map<uint16_t, uint8_t> &time_weapon_last_respawn,
             std::map<uint16_t, std::unique_ptr<Bullet>> &map_bullets,
             uint16_t &id_balas, uint16_t &id_weapons,
             std::map<uint16_t, Protection> &map_defense,
             std::map<uint16_t, Protection> &respawn_defense_points,
             uint16_t &id_defense,
             std::map<uint16_t, uint8_t> &time_defense_last_respawn);
  void movementComand(uint8_t comando, uint8_t id);
  void weaponComand(uint8_t comando, uint8_t id);
  bool inRangePickUp(float x_pos, float y_pos, float HEIGHT, float WIDTH,
                     DuckPlayer &personaje);
};

#endif // DUCK_ACTION_H
