
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
#include "weapon.h"

class GameLoop: public Thread {

private:
    BlockingQueue<CommandClient>& queue_comandos;
    bool& end_game;
    ProtectedQueuesMap& queues_map;
    Personaje personaje;
    //std::map<uint8_t, Personaje&> map_personajes;
    std::map<uint8_t,Weapon&> map_free_weapons;
    std::list<Bullet&> lista_bullets;

    void paraCadaPatoAction();

public:
    GameLoop(BlockingQueue<CommandClient>& queue_comandos, bool& end_game,
             ProtectedQueuesMap& queues_map);
    virtual void run() override;
    void checkCommand(CommandClient comando);
    void movementComand(uint8_t comando);
    void weaponComand(uint8_t comando);
    void checkBullets();
    void saltar();
    void sendCompleteScene();

    virtual ~GameLoop();
};
