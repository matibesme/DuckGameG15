#include "client.h"

Client::Client(const char* host, const char* port):
        protocolo(host, port, is_socket_close), is_socket_close(false),game() {}

void Client::execute() {
        game.run();
    
}


Client::~Client() {}
