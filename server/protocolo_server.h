#pragma once
#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>

#include "../common/dto_definitions.h"
#include "constant_definitons.h"
#include "../common/game_exception.h"

#include "../common/protocolo.h"
#include "../common/socket.h"

class ProtocoloServer {
    Socket socket_server;
    bool& dead_connection;
    Protocolo protocolo;

public:
    ProtocoloServer(Socket socket, bool& dead_connection);
    
    void sendToClient(const GameState& command);
    void sendFullGame(const GameState& command);
    /*void sendVictory(const CommandGame& command);
    void sendEndOfRound(const CommandGame& command);*/
   
    CommandClient receiveCommandFromClients();
    void closeSocket();
    ~ProtocoloServer();
};
