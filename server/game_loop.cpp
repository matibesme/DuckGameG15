#include "game_loop.h"

GameLoop::GameLoop(BlockingQueue<CommandClient>& queue_comandos, bool& end_game,
                   ProtectedQueuesMap& queues_map):
        queue_comandos(queue_comandos),
        end_game(end_game),
        queues_map(queues_map),
        personaje(1, 1, POSICION_INICIAL_X, POSICION_INICIAL_Y),
        map_free_weapons(),
        lista_bullets()
        {}

void GameLoop::run() {
    try {
        while (!end_game) {
            CommandClient comando;
            while (queue_comandos.try_pop(comando)) {
                checkCommand(comando);
            }
            paraCadaPatoAction();
            checkBullets();
            sendCompleteScene();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
        }

    } catch (const ClosedQueue& e) {
        // Queue closed
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void GameLoop::checkCommand(CommandClient comando) {
    if (comando.type_of_action == S_MOVEMENT_ACTION) {
        movementComand(comando.type_of_movement);
    } else if (comando.type_of_action == S_WEAPON_ACTION) {
        weaponComand(comando.type_of_movement);
    }
}

void GameLoop::checkBullets() {
    for (auto& bala_i : lista_bullets) {
        if (bala_i.isAlive()){
            (bala_i).executeAction();
        }

    }
}

void GameLoop::movementComand(uint8_t comando) {

    //Personaje personaje = map_personajes[1];
    if (comando==S_RIGTH){
        personaje.setXPos(MOVEMENT_QUANTITY_X);
        personaje.setTypeOfMoveSprite(S_RIGTH);
        personaje.setDirection(S_RIGTH);
    } else if (comando==S_LEFT){
        personaje.setXPos(-MOVEMENT_QUANTITY_X);
        personaje.setTypeOfMoveSprite(S_LEFT);
        personaje.setDirection(S_LEFT);
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

void GameLoop::weaponComand(uint8_t comando) {
    if (comando==S_PICKUP){
        
    } else if (comando==S_LEAVE_GUN){
        
    } else if (comando==S_SHOOT){
        Weapon weapon = personaje.getWeapon();
        if (weapon.isEmptyAmmo()){
            return;
        }
        weapon.setXPos(personaje.getXPos());
        weapon.setYPos(personaje.getYPos());    
        CowBoyBullet bullet = weapon.shoot();
        //lista_bullets.push_back(bullet);

        
    }
}

void GameLoop::sendCompleteScene(){

    CommandGame command;
    command.type_of_action = S_FULL_GAME_BYTE;
    command.scene_id = S_SCENE_ID;
    
    //recorrer map_personajes
   // for (auto& personaje_i : map_personajes) {

   DTODuck dto_duck = {personaje.getType(), personaje.getXPos(), personaje.getYPos(),
                        personaje.getTypeOfMoveSprite(), personaje.getWeapon().getType() };
   //agrego al vector de lista_patos el dto_duck
   command.lista_patos.push_back(dto_duck);

    //}
    for (auto& bala_i : lista_bullets) {
        DTOBullet dto_bullet = {bala_i.getTypeOfBullet(), bala_i.getXPos(), bala_i.getYPos(), bala_i.getDirection()};
        command.lista_balas.push_back(dto_bullet);
    }

    queues_map.sendMessagesToQueues(command);

}

void GameLoop::paraCadaPatoAction() {

    //for (Personaje& personaje_i : lista_personajes) {
        personaje.executeAction();

    //}
}

GameLoop::~GameLoop() {}
