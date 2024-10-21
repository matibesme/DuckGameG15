#pragma once
#include <string>

#include "../common/blocking_queue.h"
#include "../common/dto_definitions.h"
#include "../common/socket.h"
#include "../common/thread.h"

#include "protocolo_server.h"


class Receiver: public Thread {

private:
    BlockingQueue<CommandGameShow>& queue_receiver;
    ProtocoloCliente& protocolo;

public:
    Receiver(ProtocoloCliente& protocolo, BlockingQueue<CommandGameShow>& queue_receiver);
    virtual void run() override;
    virtual ~Receiver();
};
