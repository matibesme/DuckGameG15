#include "protected_queues_map.h"

ProtectedQueuesMap::ProtectedQueuesMap() : map_queues_sender(), m() {}

void ProtectedQueuesMap::addClient(const uint8_t &id,
                                   BlockingQueue<GameState> &queue) {
  std::lock_guard<std::mutex> lock(m);
  map_queues_sender[id] = &queue;
}

void ProtectedQueuesMap::removeQueue(const uint8_t &id) {
  std::lock_guard<std::mutex> lock(m);
  map_queues_sender.erase(id);
}

void ProtectedQueuesMap::sendMessagesToQueues(const GameState &command) {
  std::lock_guard<std::mutex> lock(m);
  for (auto it = map_queues_sender.begin(); it != map_queues_sender.end();
       ++it)
  {
    try
    {

      it->second->push(command);
    } catch (const ClosedQueue &e) {
      std::cerr << "Cola cerrada en el sender" << std::endl;
      map_queues_sender.erase(it);
      return;
    }
  }
}

bool ProtectedQueuesMap::isEmpty() {
  std::lock_guard<std::mutex> lock(m);
  return map_queues_sender.empty();
}

ProtectedQueuesMap::~ProtectedQueuesMap() {}
