#pragma once
#include <list>

#include "../common/blocking_queue.h"
#include "../common/dto_definitions.h"
#include "../common/thread.h"

#include "acceptor.h"
#include "game_loop.h"
#include "server_constant.h"

class Server {
private:
  bool close;

  Acceptor acceptor;

public:
  explicit Server(const char *port);
  void run();
  ~Server();
};
