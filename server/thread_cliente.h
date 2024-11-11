#pragma once
#include <list>
#include <string>
#include <utility>

#include "../common/blocking_queue.h"
#include "../common/dto_definitions.h"
#include "../common/socket.h"
#include "../common/thread.h"

#include "lobby_partidas.h"
#include "receiver.h"
#include "sender.h"

class ThreadCliente : public Thread {

private:
  bool dead_connection;
  std::shared_ptr<BlockingQueue<GameState>> queue_sender;
  ProtocoloServer protocolo;
  uint8_t id;
  LobbyPartidas &lobby;
  Receiver receiver;
  Sender sender;

public:
  ThreadCliente(Socket peer, uint8_t id, LobbyPartidas &lobby);
  virtual void run() override;
  void sendAction(const GameState &action);
  bool isDead();
  void delete_client();
  uint8_t getId();
  std::shared_ptr<BlockingQueue<GameState>> &getQueueSender();
  void setIsDead();
  virtual ~ThreadCliente();
};
