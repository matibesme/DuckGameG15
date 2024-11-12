#pragma once
#include <string>

#include "lobby_partidas.h"
#include "../common/blocking_queue.h"
#include "../common/dto_definitions.h"
#include "../common/socket.h"
#include "../common/thread.h"
#include "../common/common_constant.h"
#include "protocolo_server.h"

class Receiver: public Thread {

private:
    ProtocoloServer& protocolo;
    bool& dead_connection;
    bool in_lobby;
    bool start_game;
    std::shared_ptr<BlockingQueue<CommandClient>> queue_comandos;
    uint8_t id;
    LobbyPartidas &lobby;
    bool two_players;


public:
    Receiver(ProtocoloServer& protocolo, bool& dead_connection, uint8_t id_, LobbyPartidas &lobby);
    virtual void run() override;
    virtual ~Receiver();
};
