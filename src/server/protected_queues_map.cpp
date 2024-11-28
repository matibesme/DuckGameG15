#include "protected_queues_map.h"

#include "game_exception.h"

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
  for (auto it = map_queues_sender.begin(); it != map_queues_sender.end();) {
    if (it->second->isClosed()) {
      it = map_queues_sender.erase(it);
      throw ClientDisconnected();
    } else {
      it->second->push(command);
      ++it;
    }
  }
}

bool ProtectedQueuesMap::isEmpty() {
  std::lock_guard<std::mutex> lock(m);
  return map_queues_sender.empty();
}

ProtectedQueuesMap::~ProtectedQueuesMap() {}
