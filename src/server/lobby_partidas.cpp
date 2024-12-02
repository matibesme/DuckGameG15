#include "lobby_partidas.h"

LobbyPartidas::LobbyPartidas()
    : id_partida(0), partidas(), protected_queues_sender(), queues_sender(),
      queues_game_loop(), id_hoster_partida(), end_game(), map_id_clientes(),
      partidas_sin_arrancar(), m() {}

std::shared_ptr<BlockingQueue<CommandClient>>
LobbyPartidas::addPartida(uint8_t id_client, std::string &name1,
                          bool double_player, std::string &name2,
                          std::string &game_name) {
  std::lock_guard<std::mutex> lock(m);

  if (partidas_sin_arrancar.find(game_name) != partidas_sin_arrancar.end()) {
    return nullptr;
  }
  end_game[id_partida] = false;
  queues_game_loop.emplace(id_partida,
                           std::make_shared<BlockingQueue<CommandClient>>(50));
  protected_queues_sender.emplace(id_partida,
                                  std::make_unique<ProtectedQueuesMap>());
  partidas.emplace(id_partida,
                   std::make_unique<GameLoop>(
                       queues_game_loop[id_partida], end_game[id_partida],
                       protected_queues_sender[id_partida],
                       map_id_clientes[id_partida]));
  id_hoster_partida[id_client] = id_partida;
  protected_queues_sender[id_partida]->addClient(id_client,
                                                 *queues_sender[id_client]);
  //elimino la referencia en queues_sender
  queues_sender.erase(id_client);

  map_id_clientes[id_partida].emplace(id_client, name1);
  if (double_player) {
    map_id_clientes[id_partida].emplace(id_client + 1, name2);
  }
  partidas_sin_arrancar.emplace(game_name, id_partida);
  return queues_game_loop[id_partida++];
}

std::shared_ptr<BlockingQueue<CommandClient>>
LobbyPartidas::joinGame(std::string &id_partida, uint8_t id_cliente,
                        std::string &name1, bool double_player,
                        std::string &name2) {
  std::lock_guard<std::mutex> lock(m);
  if (partidas_sin_arrancar.find(id_partida) == partidas_sin_arrancar.end()) {
    return nullptr;
  }
  uint8_t id_game = partidas_sin_arrancar[id_partida];
  protected_queues_sender[id_game]->addClient(id_cliente,
                                              *queues_sender[id_cliente]);
  map_id_clientes[id_game].emplace(id_cliente, name1);
  if (double_player) {
    map_id_clientes[id_game].emplace(id_cliente + 1, name2);
  }
  return queues_game_loop[id_game];
}

bool LobbyPartidas::isHoster(uint8_t id_cliente) {
  return id_hoster_partida.find(id_cliente) != id_hoster_partida.end();
}

bool LobbyPartidas::startGame(uint8_t id_client, std::string &game_name) {
  std::lock_guard<std::mutex> lock(m);
  // chequeo si hay mas de un jugador
  if (map_id_clientes[id_hoster_partida[id_client]].size() == 1) {
    return false;
  }

  partidas[id_hoster_partida[id_client]]->start();
  partidas_sin_arrancar.erase(game_name);
  return true;
}

void LobbyPartidas::addQueueSender(
    uint8_t id_player, std::shared_ptr<BlockingQueue<GameState>> queue) {
  std::lock_guard<std::mutex> lock(m);
  queues_sender.emplace(id_player, queue);
}

void LobbyPartidas::removeGame() {
  std::lock_guard<std::mutex> lock(m);
  for (auto it = partidas.begin(); it != partidas.end();) {
    if (end_game[it->first]) {
      end_game[it->first] = true;
      queues_game_loop[it->first]->close();
      queues_game_loop.erase(it->first);
      partidas[it->first]->join();
      protected_queues_sender.erase(it->first);
      end_game.erase(it->first);
      map_id_clientes.erase(it->first);
      it = partidas.erase(it);
    } else {
      ++it;
    }
  }
}

std::map<std::string, uint8_t> &LobbyPartidas::getIdPartidas() {
  std::lock_guard<std::mutex> lock(m);
  return partidas_sin_arrancar;
}



LobbyPartidas::~LobbyPartidas() {
//recorro partidas sin arrancar

  for (auto it = partidas_sin_arrancar.begin(); it != partidas_sin_arrancar.end();) {
    end_game[it->second] = true;
    queues_game_loop[it->second]->close();
    queues_game_loop.erase(it->second);
    protected_queues_sender.erase(it->second);
    partidas.erase(it->second);
    it = partidas_sin_arrancar.erase(it);
  }
//recorro partidas arrancadas
  auto it = partidas.begin();
  while (it != partidas.end()) {
    end_game[it->first] = true;
    queues_game_loop[it->first]->close();
    queues_game_loop.erase(it->first);
    protected_queues_sender.erase(it->first);
    it->second->join();
    it = partidas.erase(it);
  }
}
