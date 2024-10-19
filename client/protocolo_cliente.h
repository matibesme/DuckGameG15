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

#include "constant_definitons.h"

class ProtocoloCliente {
    Socket socket;
    bool& dead_connection;
    Protocolo protocolo;


public:
    ProtocoloCliente(const char* host, const char* port, bool& dead_connection);

    void sendMessegeToServer(const CommandPickUp& command);
    CommandFullGame reciveFromServer();
    CommandFullGame reciveFullGameFromServer();
    CommandEndOfRound reciveEndOfRoundFromServer();
    CommandVictory reciveVictoryFromServer();

    ~ProtocoloCliente();
};
