#pragma once
#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>

#include "../common/common_constant.h"
#include "../common/dto_definitions.h"
#include "../common/game_exception.h"

#include "../common/blocking_queue.h"
#include "../common/protocolo.h"
#include "../common/socket.h"
#include <map>
#include <memory>
class ProtocoloServer {
private:
  Socket socket_server;
  bool &dead_connection;
  Protocolo protocolo;
  uint8_t id;

  void sendFinallyGame();

public:
  ProtocoloServer(Socket socket, bool &dead_connection, uint8_t id_);

  void sendToClient(const GameState &command);
  void sendFullGame(const GameState &command);
  void sendActiveGames(const std::map<std::string, uint8_t> &games);
  void sendEndRound(const GameState &command);
  void sendVictory(const GameState &command);
  void sendMatchWithSameName(bool same_name);
  void sendStartGame(bool &start_game);
  void sendDisconnectInGame();
  void
  sendPlayersColor(const std::map<std::string, std::string> &players_color);
  CommandClient receiveCommandFromClients(bool &two_players);
  GameAccess receiveAccessFromClients();

  void closeSocket();
  ~ProtocoloServer();
};
