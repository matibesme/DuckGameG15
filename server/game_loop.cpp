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
    std::list<Personaje> lista_personajes;
    std::list<Bullet> lista_balas;
    CommandGame command;
    command.type_of_action = S_FULL_GAME_BYTE;
    command.scene_id = S_SCENE_ID;
    
    for (Personaje& personaje_i : lista_personajes) {
        Personajes personaje = {personaje_i.getTypeOfPersonaje(), personaje_i.getXPos(), personaje_i.getYPos(),
                                 personaje_i.getTypeOfMoveSprite(), personaje_i.getWeapon()};
        command.personajes.push_back(personaje);
    }

    for (Bullet& bala_i : lista_balas) {
        Bullet bala = {bala_i.getTypeOfBullet(), bala_i.getXPos(), bala_i.getYPos(), bala_i.getOrientation()};
        command.bullets.push_back(bala);
    }  
  

    queues_map.sendMessagesToQueues(command);

}

void GameLoop::paraCadaPatoAction() {

    //for (Personaje& personaje_i : lista_personajes) {
        personaje.executeAction();

    //}
}

GameLoop::~GameLoop() {}
