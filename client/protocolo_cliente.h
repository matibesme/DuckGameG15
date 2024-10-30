#pragma once
#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>
#include <map>
#include "../common/dto_definitions.h"
#include "../common/game_exception.h"
//#include "../common/liberror.h"
#include "../common/protocolo.h"
#include "../common/socket.h"


#include "constant_definitons.h"
#include <vector>

class ProtocoloCliente {
    Socket socket;
    bool& dead_connection;
    Protocolo protocolo;
    std::map<uint8_t, uint8_t> decode_type_of_action;

public:
    ProtocoloCliente(const char* host, const char* port, bool& dead_connection);

   // void sendGameAccessToServer(const GameAccess& game_access);
    void sendInGameToServer(const uint8_t& command);
    GameState reciveFromServer();
    GameState reciveFullGameFromServer();
    /*CommandEndOfRound reciveEndOfRoundFromServer();
    CommandVictory reciveVictoryFromServer();*/

    ~ProtocoloCliente();
};
