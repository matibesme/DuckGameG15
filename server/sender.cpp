#include "sender.h"

#include <exception>
#include <iostream>

#include "../common/game_exception.h"
#include "../common/liberror.h"

Sender::Sender(ProtocoloServer& protocolo, BlockingQueue<CommandGame>& queue_sender,
               bool& dead_connection):
        protocolo(protocolo), queue_sender(queue_sender), dead_connection(dead_connection) {}

void Sender::run() {
    try {
        while (!dead_connection) {
            CommandGame command = queue_sender.pop();
            protocolo.sendMessegeToClients(command);
        }
    } catch (const ClosedQueue& e) {
        dead_connection = true;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}


Sender::~Sender() = default;
