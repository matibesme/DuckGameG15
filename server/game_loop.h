#pragma once
#include <chrono>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "../common/blocking_queue.h"

#include "../common/dto_definitions.h"
#include "../common/game_exception.h"
#include "../common/thread.h"

#include "../common/common_constant.h"
#include "items/ducks/duck.h"
#include "items/weapons/weapon.h"
#include "protected_queues_map.h"
// eliminar dsp
#include "items/bullets/bullet.h"

#include "configuration/load_game.h"
#include "duck_action.h"
#include "items/boxes.h"
#include "items/weapons/factory_weapons.h"
#include "server_constant.h"
class GameLoop : public Thread {

private:
  std::map<uint8_t, std::string> &map_id_clientes;
  std::shared_ptr<BlockingQueue<CommandClient>> queue_comandos;
  bool &end_game;
  std::shared_ptr<ProtectedQueuesMap> queues_map;
  std::map<uint8_t, DuckPlayer> map_personajes;

  // WEAPONS SECTION
  std::map<uint16_t, RespawnPoint> respawn_weapon_points;
  std::map<uint16_t, uint8_t> time_weapon_last_respawn;
  std::map<uint16_t, std::shared_ptr<Weapon>> map_free_weapons;
  std::list<Boxes> list_boxes;
  FactoryWeapons factory_weapons;

  std::map<uint16_t, std::unique_ptr<Bullet>> map_bullets;
  uint16_t id_balas;
  uint16_t id_weapons;
  uint8_t id_boxes;
  uint16_t id_defense;
  std::list<DTOPlatform> list_plataformas;

  std::map<uint16_t, Protection> map_defense;
  std::map<uint16_t, Protection> respawn_defense_points;
  std::map<uint16_t, uint8_t> time_defense_last_respawn;
  DuckAction duck_action;
  LoadGameFile load_game_config;

  std::map<uint8_t, uint8_t> map_victory_rounds;
  void paraCadaPatoAction();

public:
  GameLoop(std::shared_ptr<BlockingQueue<CommandClient>> &queue_comandos,
           bool &end_game, std::shared_ptr<ProtectedQueuesMap> &queues_map,
           std::map<uint8_t, std::string> &map_id_clientes);
  virtual void run() override;
  void checkCommand(CommandClient comando);
  void movementComand(uint8_t comando);
  void weaponComand(uint8_t comando);
  void checkBullets();
  void saltar();
  void sendCompleteScene();
  void checkCoalition(std::unique_ptr<Bullet> &bullet);
  void checkCoalitionDuckPlatform(DuckPlayer &personaje);
  void respawnWeapon();
  void cleanGame();
  bool checkWinner(std::string &winner);
  void sendEndRound();
  void sendVictory(std::string &winner);

  virtual ~GameLoop();
};
