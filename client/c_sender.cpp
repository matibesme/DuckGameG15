#include "c_sender.h"

#include <exception>
#include <iostream>

#include "../common/game_exception.h"

Sender::Sender(ProtocoloCliente &protocolo,
               BlockingQueue<ClientAction> &queue_sender)
    : queue_sender(queue_sender), protocolo(protocolo) {}

void Sender::run() {
  try {
    while (_keep_running) {
      ClientAction command = queue_sender.pop();
      protocolo.sendInGameToServer(command);
    }
  } catch (const std::exception &e) {
    std::cerr << "Error en el sender: " << e.what() << '\n';
    _keep_running = false;
  } catch (...) {
    std::cerr << "Error desconocido.\n";
    _keep_running = false;
  }
}

Sender::~Sender() = default;
