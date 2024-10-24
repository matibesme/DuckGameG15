#pragma once
#include <list>
#include <string>
#include <utility>

#include "../common/blocking_queue.h"
#include "../common/dto_definitions.h"
#include "../common/socket.h"
#include "../common/thread.h"

#include "receiver.h"
#include "sender.h"
#include "../common/dto_definitions.h"

class ThreadCliente: public Thread {

private:
    bool dead_connection;
    BlockingQueue<CommandClient>& queue_comandos;
    BlockingQueue<CommandGame> queue_sender;
    ProtocoloServer protocolo;
    Receiver receiver;
    Sender sender;
    uint8_t id;

public:
    ThreadCliente(Socket peer, BlockingQueue<CommandClient>& queue_comandos, uint8_t id);
    virtual void run() override;
    void sendAction(const CommandGame& action);
    bool isDead();
    void delete_client();
    uint8_t getId();
    BlockingQueue<CommandGame>& getQueueSender();
    void setIsDead();
    virtual ~ThreadCliente();
};
