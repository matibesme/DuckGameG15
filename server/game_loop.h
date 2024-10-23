
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
    std::list<Personaje> lista_personajes;
    void paraCadaPatoAction();

public:
    GameLoop(BlockingQueue<uint8_t>& queue_comandos, bool& end_game,
             ProtectedQueuesMap& queues_map);
    virtual void run() override;
    void checkCommand(uint8_t comando);
    void processCommands();
    void handleNewBox();
    void saltar();
    void sendCompleteScene();

    virtual ~GameLoop();
};
