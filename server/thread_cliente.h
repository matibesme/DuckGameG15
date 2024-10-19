#pragma once
#include <list>
#include <string>
#include <utility>

#include "../common_src/blocking_queue.h"
#include "../common_src/dto_definitions.h"
#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "receiver.h"
#include "sender.h"


class ThreadCliente: public Thread {

private:
    bool dead_connection;
    BlockingQueue<CommandPickUp>& queue_comandos;
    BlockingQueue<CommandReward> queue_sender;
    ProtocoloServer protocolo;
    Receiver receiver;
    Sender sender;
    uint8_t id;

public:
    ThreadCliente(Socket peer, BlockingQueue<CommandPickUp>& queue_comandos, uint8_t id);
    virtual void run() override;
    void sendAction(const CommandReward& action);
    bool isDead();
    void delete_client();
    uint8_t getId();
    BlockingQueue<CommandReward>& getQueueSender();
    void setIsDead();
    virtual ~ThreadCliente();
};
