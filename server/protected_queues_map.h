#pragma once
#include <list>
#include <map>
#include <mutex>
#include <string>

#include "../common_src/blocking_queue.h"
#include "../common_src/dto_definitions.h"


class ProtectedQueuesMap {
private:
    std::map<uint8_t, BlockingQueue<CommandReward>*> map_queues_sender;
    std::mutex m;

public:
    ProtectedQueuesMap();
    void addClient(const uint8_t& id, BlockingQueue<CommandReward>& queue);
    void removeQueue(const uint8_t& id);
    void sendMessagesToQueues(const CommandReward& command);
    ~ProtectedQueuesMap();
};
