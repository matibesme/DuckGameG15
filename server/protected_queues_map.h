#pragma once
#include <list>
#include <map>
#include <mutex>
#include <string>

#include "../common/blocking_queue.h"
#include "../common/dto_definitions.h"


class ProtectedQueuesMap {
private:
    std::map<uint8_t, BlockingQueue<CommandGame>*> map_queues_sender;
    std::mutex m;

public:
    ProtectedQueuesMap();
    void addClient(const uint8_t& id, BlockingQueue<CommandGame>& queue);
    void removeQueue(const uint8_t& id);
    void sendMessagesToQueues(const CommandGame& command);
    ~ProtectedQueuesMap();
};
