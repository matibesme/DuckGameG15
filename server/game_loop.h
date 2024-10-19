
#include <chrono>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <thread>
#include <vector>

#include "../common_src/blocking_queue.h"
#include "../common_src/decode_id_to_gun.h"
#include "../common_src/dto_definitions.h"
#include "../common_src/game_exception.h"
#include "../common_src/thread.h"

#include "constant_definitons.h"
#include "protected_queues_map.h"

class GameLoop: public Thread {

private:
    BlockingQueue<CommandPickUp>& queue_comandos;
    bool& end_game;

    ProtectedQueuesMap& queues_map;
    DecodeIdToGun decode_id_to_gun;
    std::map<uint8_t, uint8_t> boxes_codes;
    std::map<uint8_t, int> box_times;
    std::map<uint8_t, int> times_left_to_reappear;

public:
    GameLoop(BlockingQueue<CommandPickUp>& queue_comandos, bool& end_game,
             ProtectedQueuesMap& queues_map);
    virtual void run() override;
    void processCommands();
    void handleNewBox();
    uint8_t decodeCode(const uint8_t& code);
    bool isBoxOccupied(const uint8_t& box_id);
    bool isNewBoxAppeared();
    void setBoxOccupied(const uint8_t& box_id);


    virtual ~GameLoop();
};
