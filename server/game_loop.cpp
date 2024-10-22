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
        }
    } catch (const ClosedQueue& e) {
        // Queue closed
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}


void GameLoop::checkCommand(uint8_t comando) {
    std::cout << "Comando recibido: " << (int)comando << std::endl;
    if (comando==S_RIGTH){

        personaje.setXPos(MOVEMENT_QUANTITY_X);
        personaje.setTypeOfMoveSprite(S_RIGTH);
    } else if (comando==S_LEFT){
        personaje.setXPos(-MOVEMENT_QUANTITY_X);
        personaje.setTypeOfMoveSprite(S_LEFT);

    } else if (comando==S_JUMP && !personaje.estaSaltando()){
        saltar();
    } else if (comando==S_DOWN){
        personaje.setTypeOfMoveSprite(S_DOWN);
    }else if (comando==S_STILL && !personaje.estaSaltando()){
        personaje.setTypeOfMoveSprite(S_STILL);
    }

    sendCompleteScene();
}

void GameLoop::processCommands() {
    uint8_t comando;
    while (queue_comandos.try_pop(comando)) {
        checkCommand(comando);
    }
}

void GameLoop::saltar() {
    personaje.setEnSalto(true);
    personaje.setTypeOfMoveSprite(S_JUMP);
    float initial_pos = personaje.getYPos();

    while(personaje.getYPos() >= initial_pos - PIXELES_JUMP) {
        personaje.setYPos(-MOVEMENT_QUANTITY_Y);
        sendCompleteScene();
        // lop gao dormir un rato
        std::this_thread::sleep_for(std::chrono::milliseconds(8));

        uint8_t comando;
        if (queue_comandos.try_pop(comando)) {
            checkCommand(comando);
        }
    }

    while(personaje.getYPos() < initial_pos ) {
        personaje.setYPos(MOVEMENT_QUANTITY_Y);
        sendCompleteScene();
        uint8_t comando;
        if (queue_comandos.try_pop(comando)) {
            checkCommand(comando);
        }
    }
    personaje.setEnSalto(false);
    personaje.setTypeOfMoveSprite(S_STILL);
    sendCompleteScene();
}





void GameLoop::sendCompleteScene(){
    CommandGame command = {S_FULL_GAME_BYTE, 1, 1, {{1, 1, personaje.getXPos(), personaje.getYPos(),
                                                     personaje.getTypeOfMoveSprite()}}, 0, ""};
    std::cout<<"Se envio al cliente"<<(int)personaje.getTypeOfMoveSprite()<< std::endl;
    queues_map.sendMessagesToQueues(command);


}

GameLoop::~GameLoop() {}
