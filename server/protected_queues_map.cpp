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

void ProtectedQueuesMap::sendMessagesToQueues(const GameState &command,
                                              std::map<uint8_t, std::string> &map_id_clientes) {
  std::lock_guard<std::mutex> lock(m);
  for (auto it = map_queues_sender.begin(); it != map_queues_sender.end(); )
  {
    if (it->second->isClosed())
    {
     
      it = map_queues_sender.erase(it);
    }
    else
    {
      it->second->try_push(command);
      ++it;

    }
  }
}

bool ProtectedQueuesMap::isEmpty() {
  std::lock_guard<std::mutex> lock(m);
  return map_queues_sender.empty();
}

ProtectedQueuesMap::~ProtectedQueuesMap() {}
