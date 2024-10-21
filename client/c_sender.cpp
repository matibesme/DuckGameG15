#include "c_sender.h"

#include <exception>
#include <iostream>

#include "../common/game_exception.h"

Sender::Sender(ProtocoloCliente &protocolo, BlockingQueue<uint8_t> &queue_sender):
        queue_sender(queue_sender), protocolo(protocolo) {}

void Sender::run() {
    while (true) {
        try {
            uint8_t command = queue_sender.pop();
            protocolo.sendInGameToServer(command);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
        } catch (...) {
            std::cerr << "Error desconocido.\n";
        }
    }
}


Sender::~Sender() = default;
