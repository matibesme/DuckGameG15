#pragma once
#include <string>

#include "../common_src/blocking_queue.h"
#include "../common_src/dto_definitions.h"
#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "protocolo_server.h"

class Sender: public Thread {

private:
    ProtocoloServer& protocolo;
    BlockingQueue<CommandReward>& queue_sender;
    bool& dead_connection;


public:
    Sender(ProtocoloServer& protocolo, BlockingQueue<CommandReward>& queue_sender,
           bool& dead_connection);
    virtual void run() override;
    virtual ~Sender();
};
