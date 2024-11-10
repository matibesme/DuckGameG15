#include "client.h"
#define QUEUE_TAMANIO_MAX 1000

Client::Client(const char* host, const char* port):
        protocolo(host, port, is_socket_close), is_socket_close(false), queue_sender(QUEUE_TAMANIO_MAX),
        queue_receiver(QUEUE_TAMANIO_MAX), game(queue_sender, queue_receiver),
        sender(protocolo, queue_sender), receiver(protocolo, queue_receiver) {
                sender.start();
                receiver.start();
        }

void Client::execute() {
        game.run();
}

void Client::createGame() {
    protocolo.sendAccesToServer(CREATE_GAME, 1);
}

void Client::startGame() {
    protocolo.sendAccesToServer(START_GAME, 1);
}

void Client::joinGame(uint8_t idPartida) {
    protocolo.sendAccesToServer(JOIN_GAME, idPartida);
}

Client::~Client() {
    receiver.stop();
    sender.stop();
    receiver.join();
    sender.join();
}
