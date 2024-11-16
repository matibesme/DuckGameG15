#ifndef CLIENT_H
#define CLIENT_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include "../common/common_constant.h"
#include "../common/game_exception.h"
#include "c_receiver.h"
#include "c_sender.h"
#include "gameRunner.h"
#include "protocolo_cliente.h"

class Client {
private:
  ProtocoloCliente protocolo;
  bool is_socket_close;
  BlockingQueue<ClientAction> queue_sender;
  BlockingQueue<GameState> queue_receiver;
  GameRunner game;
  Sender sender;
  Receiver receiver;
  void execute();

public:
  Client(const char *host, const char *port);
  void createGame(bool is_double_player, std::string player_1,
                  std::string player_2, std::string game_name,
                  bool &is_available_game);
  void startGame();
  void joinGame(std::string idPartida, bool is_double_player,
                std::string player_1, std::string player_2);
  std::list<std::string> updateGame();
  ~Client();
};

#endif