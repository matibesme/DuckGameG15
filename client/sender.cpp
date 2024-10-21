#include "sender.h"

#include <exception>
#include <iostream>

#include "../common/game_exception.h"

Sender::Sender(){}

void Sender::run() {
    while (_keep_talking) {
        try {
            uint8_t command = queue_sender.pop();
            protocolo.send_command(command);
        } catch (const GameException& e) {
            std::cerr << "Error: " << e.what() << '\n';
            dead_connection = true;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
            dead_connection = true;
        } catch (...) {
            std::cerr << "Error desconocido.\n";
            dead_connection = true;
        }
    }
}


Sender::~Sender() = default;
