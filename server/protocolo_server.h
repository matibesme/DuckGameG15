#pragma once
#include <cstdint>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <utility>

#include "../common/common_constant.h"
#include "../common/dto_definitions.h"
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
    void sendActiveGames(const std::map<uint8_t, uint8_t>& games);
    void sendBackground(const GameState& command);
    CommandClient receiveCommandFromClients();
    GameAccess receiveAccessFromClients();

    void closeSocket();
    ~ProtocoloServer();
};
