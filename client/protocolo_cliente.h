#pragma once
#include <cstdint>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <utility>

#include "../common/dto_definitions.h"
#include "../common/game_exception.h"
//#include "../common/liberror.h"
#include <vector>

#include "../common/common_constant.h"
#include "../common/protocolo.h"
#include "../common/socket.h"

class ProtocoloCliente {
    Socket socket;
    bool& dead_connection;
    Protocolo protocolo;
    std::map<uint8_t, uint8_t> decode_type_of_action;

public:
    ProtocoloCliente(const char* host, const char* port, bool& dead_connection);

    // void sendGameAccessToServer(const GameAccess& game_access);
    void sendInGameToServer(const uint8_t& command);
    void sendAccesToServer(uint8_t action, uint8_t id);
    GameState reciveFromServer();
    GameState reciveFullGameFromServer();
    GameState reciveBackgroundFromServer();
    std::list<uint8_t> reciveActiveGamesFromServer();
    ~ProtocoloCliente();
};
