#pragma once
#include "../common/blocking_queue.h"
#include "../common/dto_definitions.h"
#include "../common/socket.h"
#include "../common/thread.h"
#include "protocolo_cliente.h"
#include <string>

class Receiver : public Thread {
private:
  ProtocoloCliente &protocolo;
  BlockingQueue<GameState> &queue_receiver;

public:
  Receiver(ProtocoloCliente &protocolo,
           BlockingQueue<GameState> &queue_receiver);
  virtual void run() override;
  virtual ~Receiver();
};
