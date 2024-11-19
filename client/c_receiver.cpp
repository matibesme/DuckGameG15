#include "c_receiver.h"

Receiver::Receiver(ProtocoloCliente &protocolo,
                   BlockingQueue<GameState> &queue_receiver)
    : protocolo(protocolo), queue_receiver(queue_receiver) {}

void Receiver::run() {
  try {
    while (_keep_running) {
      GameState command = protocolo.reciveFromServer();
      queue_receiver.push(command);
    }
  } catch (const std::exception &e) {
    std::cerr << "Error en el receiver: " << e.what() << '\n';
    queue_receiver.close();
  } catch (...) {
    std::cerr << "Error desconocido.\n";
    queue_receiver.close();
  }
}

Receiver::~Receiver() = default;
