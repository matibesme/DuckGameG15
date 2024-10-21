
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include "../common/game_exception.h"

#include "constant_definitons.h"
#include "protocolo_cliente.h"
#include "Game.h"

class Client {
private:
    ProtocoloCliente protocolo;
    bool is_socket_close;
    Game game;

public:
    Client(const char* host, const char* port);
    void execute();         
    ~Client();
};
