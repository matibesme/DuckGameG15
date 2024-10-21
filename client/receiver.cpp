#include "receiver.h"

//#include "../common/liberror.h"


Receiver::Receiver():{}

void Receiver::run() {
    while (_keep_talking) {
        try {
            CommandGameShow command = protocolo.receive_command();
            queue_receiver.push(command);
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


Receiver::~Receiver() = default;
