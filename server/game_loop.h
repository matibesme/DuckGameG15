
#include <chrono>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <thread>
#include <vector>
#include <memory>

#include "../common/blocking_queue.h"

#include "../common/dto_definitions.h"
#include "../common/game_exception.h"
#include "../common/thread.h"

#include "constant_definitons.h"
#include "protected_queues_map.h"
#include "items/ducks/duck.h"
#include "items/weapons/weapon.h"
//eliminar dsp
#include "items/bullets/bullet.h"
#include <yaml-cpp/yaml.h>

class GameLoop: public Thread {

private:
    BlockingQueue<CommandClient>& queue_comandos;
    bool& end_game;
    ProtectedQueuesMap& queues_map;
    std::map<uint8_t, DuckPlayer> map_personajes;
    std::map<uint8_t,std::unique_ptr<Weapon>> map_free_weapons;
    std::map<uint16_t, std::unique_ptr<Bullet>> map_bullets;
    uint16_t id_balas;
    std::list<DTOPlatform> list_plataformas;

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
    void checkCoalition(std::unique_ptr<Bullet>& bullet);
    //void checkCoalitionWithPlatform(DuckPlayer& personaje);
    void loadMap();
    virtual ~GameLoop();
};
