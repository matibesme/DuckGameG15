#pragma once
#include <string>

#include "../common/blocking_queue.h"
#include "../common/dto_definitions.h"
#include "../common/socket.h"
#include "../common/thread.h"

#include "protocolo_server.h"

class Sender: public Thread {

private:
    ProtocoloServer& protocolo;
    BlockingQueue<CommandGame>& queue_sender;
    bool& dead_connection;


public:
    Sender(ProtocoloServer& protocolo, BlockingQueue<CommandGame>& queue_sender,
           bool& dead_connection);
    virtual void run() override;
    virtual ~Sender();
};
