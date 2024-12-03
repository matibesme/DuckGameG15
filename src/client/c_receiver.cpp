#include "c_receiver.h"

Receiver::Receiver(ProtocoloCliente &protocolo,
                   BlockingQueue<GameState> &queue_receiver)
    : protocolo(protocolo), queue_receiver(queue_receiver) {}

void Receiver::run() {
  try {
    while (_keep_running) {
      GameState command = protocolo.reciveFromServer();
      queue_receiver.push(command);
      if (command.action == FINALLY_GAME || command.action == DISCONNECT_BYTE) {
        return;
      }
    }
  } catch (const std::exception &e) {
    std::cerr << "Receiver: " << e.what() << '\n';
    if (!queue_receiver.isClosed())
      queue_receiver.close();
  } catch (...) {
    std::cerr << "Error desconocido.\n";
    if (!queue_receiver.isClosed())
      queue_receiver.close();
  }
}

Receiver::~Receiver() = default;
