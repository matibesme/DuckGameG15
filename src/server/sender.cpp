#include "sender.h"

#include <exception>
#include <iostream>

#include "../common/game_exception.h"

Sender::Sender(ProtocoloServer &protocolo,
               std::shared_ptr<BlockingQueue<GameState>> queue_sender,
               bool &dead_connection)
    : protocolo(protocolo), queue_sender(queue_sender),
      dead_connection(dead_connection) {}

void Sender::run() {
  try {
    while (!dead_connection) {
      GameState command = queue_sender->pop();
      protocolo.sendToClient(command);
    }

  } catch (const ClosedQueue &e) {
    dead_connection = true;
    std::cerr << "Cola cerrada en el sender" << std::endl;
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}

Sender::~Sender() = default;
