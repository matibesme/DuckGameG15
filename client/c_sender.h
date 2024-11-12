#pragma once
#include <string>

#include "../common/blocking_queue.h"
#include "../common/dto_definitions.h"
#include "../common/socket.h"
#include "../common/thread.h"

#include "protocolo_cliente.h"

class Sender: public Thread {

private:
    BlockingQueue<ClientAction> &queue_sender;
    ProtocoloCliente &protocolo;
public:
    Sender(ProtocoloCliente &protocolo, BlockingQueue<ClientAction> &queue_sender);
    virtual void run() override;
    virtual ~Sender();
};
