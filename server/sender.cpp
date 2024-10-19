#include "sender.h"

#include <exception>
#include <iostream>

#include "../common_src/game_exception.h"
#include "../common_src/liberror.h"

Sender::Sender(ProtocoloServer& protocolo, BlockingQueue<CommandReward>& queue_sender,
               bool& dead_connection):
        protocolo(protocolo), queue_sender(queue_sender), dead_connection(dead_connection) {}

void Sender::run() {
    try {
        while (!dead_connection) {
            CommandReward command = queue_sender.pop();
            protocolo.sendMessegeToClients(command);
        }
    } catch (const ClosedQueue& e) {
        dead_connection = true;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}


Sender::~Sender() = default;
