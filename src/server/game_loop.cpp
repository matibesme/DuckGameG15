#include "game_loop.h"
#include "items/weapons/cowboy_pistol.h"
#include <bits/fs_fwd.h>
#include <bits/fs_path.h>
#include <items/weapons/duel_pistol.h>
#include <items/weapons/magnum.h>

// despues sacar
#include "items/weapons/banana.h"

GameLoop::GameLoop(
    std::shared_ptr<BlockingQueue<CommandClient>> &queue_comandos,
    bool &end_game, std::shared_ptr<ProtectedQueuesMap> &queues_map,
    std::map<uint8_t, std::string> &list_id_clientes)
    : map_id_clientes(list_id_clientes), queue_comandos(queue_comandos),
      end_game(end_game), queues_map(queues_map), map_personajes(),
      respawn_weapon_points(), time_weapon_last_respawn(), map_free_weapons(),
      factory_weapons(), map_bullets(), id_balas(0), id_weapons(0), id_boxes(0),
      id_defense(0), list_plataformas(), map_defense(),
      respawn_defense_points(), time_defense_last_respawn(),
      list_colors({"red", "blue", "green", "yellow", "pink", "purple", "orange",
                   "brown", "black", "white"}),
      duck_action(map_personajes, map_free_weapons, respawn_weapon_points,
                  time_weapon_last_respawn, map_bullets, id_balas, id_weapons,
                  map_defense, respawn_defense_points, id_defense,
                  time_defense_last_respawn),
      load_game_config(factory_weapons, list_plataformas, respawn_weapon_points,
                       map_defense, respawn_defense_points, id_defense,
                       id_weapons, id_boxes, map_free_weapons, list_boxes,
                       map_bullets, id_balas, map_personajes, map_id_clientes,
                       list_colors, scene_id),
      map_victory_rounds(),
      scene_id(0),
      dead_players() {}

void GameLoop::run() {
  try {
    load_game_config.loadConfigurations();
    sendColorPresentation();

    while (!end_game) {
      uint8_t rounds = 0;
      while (!end_game && rounds < GAMES_PER_ROUND) {
        load_game_config.loadGame();

        while (!end_game && map_personajes.size() > 1) {
          CommandClient comando;
          while (queue_comandos->try_pop(comando)) {
            checkCommand(comando, rounds);
          }
          if (queues_map->isEmpty()) {
            end_game = true;
            break;
          }
          paraCadaPatoAction();
          checkBullets();
          respawnWeapon();
          sendCompleteScene();
          std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
        }
        if (map_personajes.size() < 1) {
          cleanGame();
          continue;
        }
        map_victory_rounds[map_personajes.begin()->first]++;
        rounds++;
        cleanGame();
      }
      std::string winner;
      bool win = checkWinner(winner);
      if (win) {
        sendVictory(winner);
        end_game = true;
        break;
      }
      sendEndRound();
    }

    // send round status
    GameState command;
    command.action = FINALLY_GAME;
    queues_map->sendMessagesToQueues(command);
  } catch (const ClosedQueue &e) {
    // Queue closed
    std::cerr << "Cola cerrada en el game loop" << std::endl;
  } catch (const ClientDisconnected &e) {
    std::cerr << "Cliente desconectado" << std::endl;

    GameState command;
    command.action = DISCONNECT_BYTE;
    queues_map->sendMessagesToQueues(command);
    end_game = true;
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}

void GameLoop::checkCommand(CommandClient comando, uint8_t &rounds) {
  if (map_personajes.find(comando.id) == map_personajes.end()) {
    return;
  }
  if (comando.type_of_action == MOVEMENT_ACTION) {
    duck_action.movementComand(comando.type_of_movement, comando.id);
  } else if (comando.type_of_action == WEAPON_ACTION) {
    duck_action.weaponComand(comando.type_of_movement, comando.id);
  } else if (comando.type_of_action == CHEAT_ACTION) {
    if (comando.type_of_movement == CHEAT_SPAWN_BOX) {
      spawnBoxesCheat();
    } else if (comando.type_of_movement == CHEAT_WIN_ROUND) {
      winRoundCheat();
    } else if (comando.type_of_movement == CHEAT_WIN_GAME) {
      winGameCheat(rounds);
    } else {
      duck_action.cheatComand(comando.type_of_movement, comando.id);
    }
  }
}

void GameLoop::checkBullets() {
  for (auto it = map_bullets.begin(); it != map_bullets.end();) {
    if (!it->second->isAlive()) {
      if (it->second->getTypeOfBullet() == GRENADE_EXPLOSION) {
        checkGrenadeExplosion(*(GranadaBullet *)it->second.get());
      }
      it = map_bullets.erase(it);
    } else {
      checkCoalition(it->second);
      it->second->executeAction();
      ++it;
    }
  }
}

void GameLoop::sendCompleteScene() {
  GameState command;
  command.action = FULL_GAME_BYTE;
  command.backGround_id = scene_id;

  for (auto &platform : list_plataformas) {
    command.lista_plataformas.push_back(platform);
  }

  for (auto &personaje : map_personajes) {
    uint8_t weapon_type = NOGUN;
    if (personaje.second.isWeaponEquipped()) {
      weapon_type = personaje.second.getWeapon().getType();
    }
    DTODuck dto_duck = {personaje.first,
                        personaje.second.getColor(),
                        personaje.second.getXPos(),
                        personaje.second.getYPos(),
                        personaje.second.getTypeOfMoveSprite(),
                        weapon_type,
                        personaje.second.getHelmet(),
                        personaje.second.getArmor(),
                        personaje.second.isAimingUp(),
                        personaje.second.getDirection()};

    command.lista_patos.push_back(dto_duck);
  }

  for (auto &personaje : dead_players) {
    uint8_t weapon_type = NOGUN;
    if (personaje.isWeaponEquipped()) {
      weapon_type = personaje.getWeapon().getType();
    }
    DTODuck dto_duck = {personaje.getId(),
                        personaje.getColor(),
                        personaje.getXPos(),
                        personaje.getYPos(),
                        personaje.getTypeOfMoveSprite(),
                        weapon_type,
                        personaje.getHelmet(),
                        personaje.getArmor(),
                        personaje.isAimingUp(),
                        personaje.getDirection()};

    command.lista_patos.push_back(dto_duck);
  }
  for (auto &bullet : map_bullets) {
    DTOBullet dto_bullet = {bullet.first, bullet.second->getType(),
                            bullet.second->getXPos(), bullet.second->getYPos(),
                            bullet.second->getDirection()};
    command.lista_balas.push_back(dto_bullet);
  }

  for (auto &weapon : map_free_weapons) {
    DTOGuns dto_gun = {weapon.second->getType(), weapon.second->getXPos(),
                       weapon.second->getYPos()};
    command.lista_guns.push_back(dto_gun);
  }

  for (auto &box : list_boxes) {
    DTOBoxes dto_box = {box.getId(), box.getXPos(), box.getYPos()};
    command.lista_boxes.push_back(dto_box);
  }

  for (auto &defense : map_defense) {
    if (defense.second.type == HELMET_EQUIPPED) {
      command.lista_helmets.push_back(defense.second);
    } else {
      command.lista_armors.push_back(defense.second);
    }
  }

  queues_map->sendMessagesToQueues(command);
}

void GameLoop::paraCadaPatoAction() {
  for (auto it = map_personajes.begin(); it != map_personajes.end();) {
    checkCoalitionDuckPlatform(it->second);
    it->second.executeAction();

    if (!it->second.isAlive()) {
      dead_players.push_back(it->second);
      it = map_personajes.erase(it);
      continue;
    }

    if (!it->second.isWeaponEquipped()) {
      ++it; // Solo avanza el iterador si no hay eliminación
      continue;
    }

    if (it->second.getWeapon().getType() == GRANADA_GUN &&
        it->second.getWeapon().isActive()) {
      std::unique_ptr<Bullet> bullet =
          it->second.getWeapon().shoot(it->second.isAimingUp());
      map_bullets.emplace(id_balas, std::move(bullet));
      id_balas++;
      it->second.eraseGun();
    }

    ++it;
  }
}

void GameLoop::checkCoalition(std::unique_ptr<Bullet> &bullet) {
  for (auto &plataform : list_plataformas) {
    bullet->colisionWithPlatform(plataform.x_pos, plataform.y_pos,
                                 plataform.width, plataform.height + 5);
  }
  uint8_t bullet_type = bullet->getTypeOfBullet();
  if (bullet_type != GRANADA_BULLET) {
    for (auto it = map_personajes.begin(); it != map_personajes.end();) {
      bool colision = bullet->colisionWithDuck(
          it->second.getXPos(), it->second.getYPos(), DUCK_WIDTH, DUCK_HEIGHT);
      if (colision) {
        if (bullet_type == BANANA_BULLET) {
          it->second.setIsSliding(true);
          return;
        }
        if (it->second.receiveShoot()) {
          it->second.applyDamage(bullet->getDamage());
        }
        if (!it->second.isAlive()) {
          dead_players.push_back(it->second);
          it = map_personajes.erase(it);
        } else {
          ++it;
        }
        return;
      } else {
        ++it;
      }
    }
  }

  for (auto it = list_boxes.begin(); it != list_boxes.end();) {
    bool colision = bullet->colisionWithBox(it->getXPos(), it->getYPos(),
                                            WIDTH_BOX, HEIGHT_BOX);
    if (colision) {
      it->takeDamage(bullet->getDamage());
      if (it->isDestroyed()) {
        it = list_boxes.erase(it);
        break;
      } else {
        ++it;
      }
    } else {
      ++it;
    }
  }
}

void GameLoop::checkCoalitionDuckPlatform(DuckPlayer &personaje) {
  bool is_on_platform = false;
  for (auto &platform : list_plataformas) {
    if (sobrePlataformaX(personaje, platform)) {
      bool is_on_platform_down = false;
      coalisionSuperiorEinferior(personaje, platform, is_on_platform,
                                 is_on_platform_down);
      if (is_on_platform_down)
        return;
    }
    coalisonWalls(personaje, platform);
  }

  if (!is_on_platform && (!personaje.estaSaltando() || personaje.isSliding())) {
    personaje.setRespondAfterSliding(15);
    personaje.setIsSliding(false);
    personaje.setEnSalto(true);
    personaje.setVelocidadY(0);
  }
}

bool GameLoop::sobrePlataformaX(DuckPlayer &personaje, DTOPlatform &platform) {
  return (personaje.getXPos() >= platform.x_pos &&
          personaje.getXPos() <=
              platform.x_pos + platform.width - MARGEN_DESPLAZAMIENTO_PATO_X) ||
         (personaje.getXPos() <= platform.x_pos &&
          personaje.getXPos() + (DUCK_WIDTH - MARGEN_DESPLAZAMIENTO_PATO_X) >=
              platform.x_pos) ||
         (personaje.getXPos() <=
              platform.x_pos + platform.width - MARGEN_DESPLAZAMIENTO_PATO_X &&
          personaje.getXPos() + DUCK_WIDTH - MARGEN_DESPLAZAMIENTO_PATO_X >=
              platform.x_pos + platform.width - MARGEN_DESPLAZAMIENTO_PATO_X);
}

void GameLoop::coalisionSuperiorEinferior(DuckPlayer &personaje,
                                          DTOPlatform &platform,
                                          bool &is_on_platform,
                                          bool &is_on_platform_down) {
  if (personaje.getYPos() + DUCK_HEIGHT >=
          platform.y_pos - PLATAFORMA_LEVEMENTE_LEVANTADA &&
      personaje.getYPos() + personaje.getVelocidadY() <= platform.y_pos) {
    if (personaje.getVelocidadY() < 0) {
      personaje.stopJump(platform.y_pos - DUCK_HEIGHT);
    } else {
      personaje.setYPos(platform.y_pos - DUCK_HEIGHT);
    }
    is_on_platform = true;
  } if (personaje.getYPos() <= platform.y_pos + platform.height &&
             personaje.getYPos() + DUCK_HEIGHT >
                 platform.y_pos + platform.height &&
             personaje.getVelocidadY() > 0) {
    if (personaje.getXPos() >= platform.x_pos + platform.width -
                                   MARGEN_DESPLAZAMIENTO_PLATAFORMA_X_IZQ) {
      return;
    }
    personaje.setYPos(platform.y_pos + platform.height);
    personaje.setVelocidadY(0);
    is_on_platform_down = true;
  }
}

void GameLoop::coalisonWalls(DuckPlayer &personaje, DTOPlatform &platform) {
  if (personaje.getYPos() + DUCK_HEIGHT - DUCK_HEIGHT / 3 > platform.y_pos &&
      personaje.getYPos() < platform.y_pos + platform.height) {
    if (personaje.isWeaponEquipped()) {
      if (personaje.getXPos() + DUCK_WIDTH - DESPLAZAMIENTO_CON_ARMA_X >
              platform.x_pos &&
          personaje.getXPos() < platform.x_pos &&
          personaje.getDirection() == RIGHT) {
        personaje.setXPos(platform.x_pos - DUCK_WIDTH +
                          DESPLAZAMIENTO_CON_ARMA_X);
      } else if (personaje.getXPos() - MARGEN_DESPLAZAMIENTO_PLATAFORMA_X <
                     platform.x_pos + platform.width -
                         MARGEN_DESPLAZAMIENTO_PLATAFORMA_X &&
                 personaje.getXPos() - MARGEN_DESPLAZAMIENTO_PLATAFORMA_X >
                     platform.x_pos &&
                 personaje.getDirection() == LEFT) {
        personaje.setXPos(platform.x_pos + platform.width);
      }
      return;
    }

    if (personaje.getXPos() + DUCK_WIDTH - MARGEN_DESPLAZAMIENTO_PATO_X_WALL >
            platform.x_pos &&
        personaje.getXPos() < platform.x_pos &&
        personaje.getDirection() == RIGHT) {
      personaje.setXPos(platform.x_pos - DUCK_WIDTH +
                        MARGEN_DESPLAZAMIENTO_PATO_X_WALL);
    } else if (personaje.getXPos() -4< platform.x_pos + platform.width -
                                         MARGEN_DESPLAZAMIENTO_PLATAFORMA_X &&
               personaje.getXPos() > platform.x_pos &&
               personaje.getDirection() == LEFT) {
      personaje.setXPos(platform.x_pos + platform.width -
                        MARGEN_DESPLAZAMIENTO_PLATAFORMA_X);
    }
  }
}
void GameLoop::respawnWeapon() {
  for (auto it = time_weapon_last_respawn.begin();
       it != time_weapon_last_respawn.end();) {
    if (it->second == 0) {
      RespawnPoint &weapon = respawn_weapon_points[it->first];
      map_free_weapons.emplace(
          it->first, factory_weapons.createWeapon(weapon.type, weapon.x_pos,
                                                  weapon.y_pos));
      it = time_weapon_last_respawn.erase(it);
    } else {
      it->second--;

      ++it;
    }
  }

  for (auto it = time_defense_last_respawn.begin();
       it != time_defense_last_respawn.end();) {
    if (it->second == 0) {
      Protection &defense = respawn_defense_points[it->first];
      map_defense.emplace(it->first, defense);
      it = time_defense_last_respawn.erase(it);
    } else {
      it->second--;
      ++it;
    }
  }
}

void GameLoop::cleanGame() {
  map_personajes.clear();
  map_bullets.clear();
  map_free_weapons.clear();
  list_boxes.clear();
  map_defense.clear();
  respawn_defense_points.clear();
  time_defense_last_respawn.clear();
  time_weapon_last_respawn.clear();
  respawn_weapon_points.clear();
  id_balas = 0;
  id_weapons = 0;
  id_boxes = 0;
  id_defense = 0;
  list_plataformas.clear();
  dead_players.clear();
}

bool GameLoop::checkWinner(std::string &winner) {
  uint8_t cant_winners = 0;
  uint8_t max_victories = 0;
  for (auto &victory_round : map_victory_rounds) {
    if (victory_round.second >= NECESARY_VICTORY_ROUNDS) {
      if (victory_round.second > max_victories) {
        max_victories = victory_round.second;
        winner = map_id_clientes[victory_round.first];
        cant_winners = 1;

      } else if (victory_round.second == max_victories) {
        cant_winners++;
      }
    }
  }
  return cant_winners == 1;
}

void GameLoop::sendEndRound() {
  GameState command;
  command.action = END_ROUND_BYTE;
  for (auto &victory_round : map_victory_rounds) {
    command.map_victorias.emplace(map_id_clientes[victory_round.first],
                                  victory_round.second);
  }

  for (int i = 0; i < 100; i++) {
    queues_map->sendMessagesToQueues(command);
  }
}

void GameLoop::sendVictory(std::string &winner) {
  GameState command;
  command.action = VICTORY_BYTE;
  command.name_winner = winner;

  for (int i = 0; i < 150; i++) {
    queues_map->sendMessagesToQueues(command);
  }

  command.action = FINALLY_GAME;
  queues_map->sendMessagesToQueues(command);
}

void GameLoop::spawnBoxesCheat() {
  for (auto &personaje : map_personajes) {
    list_boxes.emplace_back(
        Boxes(TYPE_BOX, id_boxes++, personaje.second.getXPos(),
              personaje.second.getYPos(), 100, map_free_weapons, map_defense,
              map_bullets, id_balas, id_weapons, id_defense));
  }
}

void GameLoop::winRoundCheat() {
  auto it = map_personajes.begin(); // Obtén el primer elemento
  if (it != map_personajes.end()) {
    ++it; // Mueve el iterador al segundo elemento
    while (it != map_personajes.end()) {
      auto to_erase = it; // Guarda el iterador actual
      ++it;               // Avanza al siguiente elemento antes de eliminar
      map_personajes.erase(to_erase); // Elimina el elemento
    }
  }
}

void GameLoop::winGameCheat(uint8_t &rounds) {
  map_victory_rounds[map_personajes.begin()->first] = 9;
  rounds = 4;
  winRoundCheat();
}

void GameLoop::sendColorPresentation() {
  GameState command;
  command.action = COLOR_PRESENTATION_BYTE;
  uint8_t indice = 0;
  for (auto &player : map_id_clientes) {
    command.players_color.emplace(player.second, list_colors[indice++]);
    map_victory_rounds.emplace(player.first, VICTORY_ROUNDS_INICIAL);
  }
  for (int i = 0; i < 100; i++) {
    queues_map->sendMessagesToQueues(command);
  }
}

void GameLoop::checkGrenadeExplosion(GranadaBullet &grenade_bullet) {
  if (grenade_bullet.isExplode()) {
    return;
  }
  grenade_bullet.setIsExplode(true);
  for (auto it = map_personajes.begin(); it != map_personajes.end();) {
    if (grenade_bullet.getXPos() - (RADIO_EXPLOTION_GRANADA * DUCK_WIDTH) <
            it->second.getXPos() &&
        grenade_bullet.getXPos() + (RADIO_EXPLOTION_GRANADA * DUCK_WIDTH) >
            it->second.getXPos() &&
        grenade_bullet.getYPos() - (RADIO_EXPLOTION_GRANADA * DUCK_HEIGHT) <
            it->second.getYPos() &&
        grenade_bullet.getYPos() + (RADIO_EXPLOTION_GRANADA * DUCK_HEIGHT) >
            it->second.getYPos()) {

      if (it->second.receiveShoot()) {
        it->second.applyDamage(grenade_bullet.getDamage());
      }
      if (!it->second.isAlive()) {
        dead_players.push_back(it->second);
        it = map_personajes.erase(it);
      } else {
        ++it;
      }
    } else {
      ++it;
    }
  }
  for (auto it = list_boxes.begin(); it != list_boxes.end();) {
    if (grenade_bullet.getXPos() - (RADIO_EXPLOTION_GRANADA * WIDTH_BOX) <
            it->getXPos() &&
        grenade_bullet.getXPos() + (RADIO_EXPLOTION_GRANADA * WIDTH_BOX) >
            it->getXPos() &&
        grenade_bullet.getYPos() - (RADIO_EXPLOTION_GRANADA * HEIGHT_BOX) <
            it->getYPos() &&
        grenade_bullet.getYPos() + (RADIO_EXPLOTION_GRANADA * HEIGHT_BOX) >
            it->getYPos()) {
      it->takeDamage(grenade_bullet.getDamage());
      if (it->isDestroyed()) {
        it = list_boxes.erase(it);
      } else {
        ++it;
      }
    } else {
      ++it;
    }
  }
}

GameLoop::~GameLoop() {}
