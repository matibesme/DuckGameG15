#include "server.h"


Server::Server(const char* port):
        close(false),
        map_queues_sender(),
        queue_comandos(50),
        acceptor(port, map_queues_sender, queue_comandos, close),
        game_loop(queue_comandos, close, map_queues_sender) {}


void Server::run() {
    try {

        acceptor.start();
        game_loop.start();

        while (std ::cin.get() != SALIDA) {}
        close = true;

        acceptor.closeSocket();
        queue_comandos.close();
        acceptor.join();
        game_loop.join();

    } /*catch (const std::exception& e) {
        std::cerr << e.what() << "Error en el socket, mirar servidor" << std::endl;
    }*/ catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}


Server::~Server() {}
