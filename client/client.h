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
  BlockingQueue<uint8_t> queue_sender;
  BlockingQueue<GameState> queue_receiver;
  GameRunner game;
  Sender sender;
  Receiver receiver;
  void execute();

public:
  Client(const char *host, const char *port);
  void createGame();
  void startGame();
  void joinGame(uint8_t idPartida);
  std::list<uint8_t> updateGame(uint8_t key);
  ~Client();
};

#endif