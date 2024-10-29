#include "protected_queues_map.h"

ProtectedQueuesMap::ProtectedQueuesMap(): map_queues_sender(), m() {}

void ProtectedQueuesMap::addClient(const uint8_t& id, BlockingQueue<GameState>& queue) {
    std::lock_guard<std::mutex> lock(m);
    map_queues_sender[id] = &queue;
}


void ProtectedQueuesMap::removeQueue(const uint8_t& id) {
    std::lock_guard<std::mutex> lock(m);
    map_queues_sender.erase(id);
}

void ProtectedQueuesMap::sendMessagesToQueues(const GameState& command) {
    std::lock_guard<std::mutex> lock(m);
    for (auto it = map_queues_sender.begin(); it != map_queues_sender.end(); ++it) {
        it->second->push(command);
    }
}

ProtectedQueuesMap::~ProtectedQueuesMap() {}
