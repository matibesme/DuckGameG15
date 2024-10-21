#include "c_receiver.h"

//#include "../common/liberror.h"

Receiver::Receiver(ProtocoloCliente& protocolo, BlockingQueue<CommandGameShow>& queue_receiver) :
    protocolo(protocolo), queue_receiver(queue_receiver) {}

void Receiver::run() {
    while (true) {
        try {
            CommandGameShow command = protocolo.reciveFromServer();
            queue_receiver.push(command);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
        } catch (...) {
            std::cerr << "Error desconocido.\n";
        }
    }
    
}

Receiver::~Receiver() = default;
