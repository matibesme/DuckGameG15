#include "server.h"


Server::Server(const char* port):
        close(false),
        acceptor(port, close) {}


void Server::run() {
    try {

        acceptor.start();


        while (std ::cin.get() != SALIDA) {}
        close = true;

        acceptor.closeSocket();
        acceptor.join();


    } /*catch (const std::exception& e) {
        std::cerr << e.what() << "Error en el socket, mirar servidor" << std::endl;
    }*/ catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}


Server::~Server() {}
