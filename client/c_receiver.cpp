#include "c_receiver.h"

//#include "../common/liberror.h"

Receiver::Receiver(ProtocoloCliente& protocolo, BlockingQueue<GameState>& queue_receiver) :
    protocolo(protocolo), queue_receiver(queue_receiver) {}

void Receiver::run() {

    while (_keep_running) {
        try {
            GameState command = protocolo.reciveFromServer();
            queue_receiver.push(command);
        } catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
            _keep_running = false;
        } catch (...) {
          std::cerr << "Error desconocido.\n";
          _keep_running = false;
        }
    }
    queue_receiver.close();
}

Receiver::~Receiver() = default;
