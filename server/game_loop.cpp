#include "game_loop.h"


GameLoop::GameLoop(BlockingQueue<uint8_t>& queue_comandos, bool& end_game,
                   ProtectedQueuesMap& queues_map):
        queue_comandos(queue_comandos),
        end_game(end_game),
        queues_map(queues_map),
        personaje() {}

void GameLoop::run() {
    try {
        while (!end_game) {
           
            processCommands();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    } catch (const ClosedQueue& e) {
        // Queue closed
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}



void GameLoop::processCommands() {
    uint8_t comando;
    while (queue_comandos.try_pop(comando)) {
        if (comando==RIGTH){
            personaje.setXPos(MOVEMENT_QUANTITY,true);
            personaje.setOrientation(ORIENTATION_RIGTH);
        } else if (comando==LEFT){
            personaje.setXPos(MOVEMENT_QUANTITY,false);
            personaje.setOrientation(ORIENTATION_LEFT);
        } else if (comando==JUMP){
            //personaje.setYPos(-1);
        } else if (comando==DOWN){
            //personaje.setYPos(1);
        } 


        CommandGame command = {FULL_GAME_BYTE, 1, 1, {{1, 1, personaje.getXPos(), personaje.getYPos(), personaje.getOrientation()}}, 0,""};
        queues_map.sendMessagesToQueues(command);
    }

}



GameLoop::~GameLoop() {}
