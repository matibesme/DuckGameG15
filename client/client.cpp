#include "client.h"

Client::Client(const char* host, const char* port):
        protocolo(host, port, is_socket_close), is_socket_close(false), queue_sender(TAMANIO_MAX),
        queue_receiver(TAMANIO_MAX), game(protocolo, queue_sender, queue_receiver),
        sender(protocolo, queue_sender), receiver(protocolo, queue_receiver) {
                sender.start();
                receiver.start();
        }

void Client::execute() {
        game.run();
}


Client::~Client() {
    receiver.stop();
    sender.stop();
    receiver.join();
    sender.join();
}
