#include "game_loop.h"


GameLoop::GameLoop(BlockingQueue<uint8_t>& queue_comandos, bool& end_game,
                   ProtectedQueuesMap& queues_map):
        queue_comandos(queue_comandos),
        end_game(end_game),
        queues_map(queues_map),
        //personaje(),
        map_free_weapons(),
        map_personajes()
        {}

void GameLoop::run() {
    try {
        while (!end_game) {
            uint8_t comando;
            while (queue_comandos.try_pop(comando)) {
                checkCommand(comando);
            }
            paraCadaPatoAction();
            sendCompleteScene();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
        }

    } catch (const ClosedQueue& e) {
        // Queue closed
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void GameLoop::checkCommand(uint8_t comando) {

    if (comando==S_RIGTH){
        personaje.setXPos(MOVEMENT_QUANTITY_X);
        personaje.setTypeOfMoveSprite(S_RIGTH);
    } else if (comando==S_LEFT){
        personaje.setXPos(-MOVEMENT_QUANTITY_X);
        personaje.setTypeOfMoveSprite(S_LEFT);
    } else if (comando==S_JUMP && !personaje.estaSaltando()){
        personaje.setEnSalto(true);
        personaje.setTypeOfMoveSprite(S_JUMP);
    } else if (comando==S_DOWN){
        personaje.setTypeOfMoveSprite(S_DOWN);
    }else if (comando==S_STILL){
        personaje.setTypeOfMoveSprite(S_STILL);
    }

    //sendCompleteScene();  //comento nose si esta bien? tal vez deberia mandar siempre la escena completa
}

void GameLoop::sendCompleteScene(){
    
    uint8_t personajes_type;//the character
    float x_pos;
    float y_pos;
    uint8_t typeOfMove;//right left down jump still
    uint8_t typeOfGun; // nogun, cowboy ...
    
    CommandGame command = {S_FULL_GAME_BYTE, S_PERSONAJE_TYPE, 1, {{ 1, personaje.getXPos(), personaje.getYPos(),
                                                     personaje.getTypeOfMoveSprite(), personaje.getWeapon()}}, 0, ""};
    

    queues_map.sendMessagesToQueues(command);

}

void GameLoop::paraCadaPatoAction() {

    //for (Personaje& personaje_i : lista_personajes) {
        personaje.executeAction();

    //}
}

GameLoop::~GameLoop() {}
