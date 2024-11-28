#pragma once
#include "../common/blocking_queue.h"
#include "../common/dto_definitions.h"
#include "game_loop.h"
#include "protected_queues_map.h"
#include <map>
#include <memory>
#include <mutex>
#include <string>
class ThreadCliente;
class LobbyPartidas {
private:
  uint8_t id_partida;
  std::map<uint8_t, std::unique_ptr<GameLoop>> partidas;
  std::map<uint8_t, std::shared_ptr<ProtectedQueuesMap>>
      protected_queues_sender;
  std::map<uint8_t, std::shared_ptr<BlockingQueue<GameState>>> queues_sender;
  std::map<uint8_t, std::shared_ptr<BlockingQueue<CommandClient>>>
      queues_game_loop;
  std::map<uint8_t, uint8_t> id_hoster_partida;
  std::map<uint8_t, bool> end_game;
  std::map<uint8_t, std::map<uint8_t, std::string>> map_id_clientes;
  std::map<std::string, uint8_t> partidas_sin_arrancar;
  std::mutex m;

public:
  LobbyPartidas();
  std::shared_ptr<BlockingQueue<CommandClient>>
  addPartida(uint8_t id_cliente, std::string &name1, bool double_player,
             std::string &name2, std::string &game_name);
  void removePartida(uint8_t id_partida);
  std::shared_ptr<BlockingQueue<CommandClient>>
  joinGame(std::string &id_partida, uint8_t id_cliente, std::string &name1,
           bool double_player, std::string &name2);
  void addQueueSender(uint8_t id_player,
                      std::shared_ptr<BlockingQueue<GameState>> queue);
  bool isHoster(uint8_t id_cliente);
  bool startGame(uint8_t id_client, std::string &game_name);
  void removeGame();
  std::map<std::string, uint8_t> &getIdPartidas();
  ~LobbyPartidas();
};
