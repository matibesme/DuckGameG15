#pragma once
#include <string>

#include "../common/blocking_queue.h"
#include "../common/dto_definitions.h"
#include "../common/socket.h"
#include "../common/thread.h"

#include "protocolo_server.h"


class Receiver: public Thread {

private:
    ProtocoloServer& protocolo;
    bool& dead_connection;
    bool in_game;
    BlockingQueue<CommandGame>& queue_comandos;


public:
    Receiver(ProtocoloServer& protocolo, bool& dead_connection,
             BlockingQueue<CommandGame>& queue_comandos);
    virtual void run() override;
    virtual ~Receiver();
};
