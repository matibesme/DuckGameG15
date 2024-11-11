#pragma once
#include <list>
#include <utility>

#include "../common/blocking_queue.h"
#include "../common/liberror.h"
#include "../common/socket.h"
#include "../common/thread.h"

#include "lobby_partidas.h"
#include "protected_queues_map.h"
#include "thread_cliente.h"

class Acceptor : public Thread {

private:
  Socket socket_servidor;
  std::list<ThreadCliente> lista_clientes;
  bool &close;
  uint8_t cantidad_clientes;
  LobbyPartidas lobby;

public:
  Acceptor(const char *port, bool &close); // saco el queue_Sender
  virtual void run() override;
  void accept_new_client();
  void deleteAClient(ThreadCliente &cliente);
  void reapDead();
  void closeSocket();

  virtual ~Acceptor();
};
