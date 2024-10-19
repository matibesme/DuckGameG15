#pragma once
#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>

#include "../common_src/dto_definitions.h"
#include "../common_src/game_exception.h"
#include "../common_src/liberror.h"
#include "../common_src/protocolo.h"
#include "../common_src/socket.h"

class ProtocoloServer {
    Socket socket_server;
    bool& dead_connection;
    Protocolo protocolo;

public:
    ProtocoloServer(Socket socket, bool& dead_connection);

    void sendFullGame(const CommandFullGame& command);
    void sendVictory(const CommandVictory& command);
    void sendEndOfRound(const CommandEndOfRound& command);
    CommandClient receiveCommandFromClients();
    void closeSocket();
    ~ProtocoloServer();
};
