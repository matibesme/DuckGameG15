#pragma once
#include <string>

#include "../common_src/blocking_queue.h"
#include "../common_src/dto_definitions.h"
#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "protocolo_server.h"


class Receiver: public Thread {

private:
    ProtocoloServer& protocolo;
    bool& dead_connection;
    BlockingQueue<CommandPickUp>& queue_comandos;


public:
    Receiver(ProtocoloServer& protocolo, bool& dead_connection,
             BlockingQueue<CommandPickUp>& queue_comandos);
    virtual void run() override;
    virtual ~Receiver();
};
