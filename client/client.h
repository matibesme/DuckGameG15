
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include "../common/game_exception.h"

#include "constant_definitons.h"
#include "protocolo_cliente.h"
#include "gameRunner.h"
#include "c_sender.h"
#include "c_receiver.h"

class Client {
private:
    ProtocoloCliente protocolo;
    bool is_socket_close;
    BlockingQueue<uint8_t> queue_sender;
    BlockingQueue<CommandGameShow> queue_receiver;
    GameRunner game;
    Sender sender;
    Receiver receiver;

public:
    Client(const char* host, const char* port);
    void execute();         
    ~Client();
};
