
#include <chrono>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <thread>
#include <vector>

#include "../common/blocking_queue.h"

#include "../common/dto_definitions.h"
#include "../common/game_exception.h"
#include "../common/thread.h"

#include "constant_definitons.h"
#include "protected_queues_map.h"
#include "personaje.h"

class GameLoop: public Thread {

private:
    BlockingQueue<uint8_t>& queue_comandos;
    bool& end_game;
    ProtectedQueuesMap& queues_map;
    Personaje personaje;
    std::map<uint8_t, > boxes;

public:
    GameLoop(BlockingQueue<CommandGame>& queue_comandos, bool& end_game,
             ProtectedQueuesMap& queues_map);
    virtual void run() override;
    void processCommands();
    void handleNewBox();



    virtual ~GameLoop();
};
