#include "game_loop.h"

GameLoop::GameLoop(BlockingQueue<CommandClient>& queue_comandos, bool& end_game,
                   ProtectedQueuesMap& queues_map):
        queue_comandos(queue_comandos),
        end_game(end_game),
        queues_map(queues_map),
        map_personajes(),
        map_free_weapons(),
        map_bullets(),
        id_balas(1)
        {}

void GameLoop::run() {
    try {

        map_personajes.emplace(1, DuckPlayer(1, 1, S_POSICION_INICIAL_X, S_POSICION_INICIAL_Y));

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
    for (auto it = map_bullets.begin(); it != map_bullets.end(); ) {
        if (!it->second->isAlive()) {
            it = map_bullets.erase(it);     
        } else {
            it->second->executeAction();
            checkCoalition(it->second);
            ++it;
        }
    }
}

void GameLoop::movementComand(uint8_t comando) {
    DuckPlayer& personaje = map_personajes[1];

    if (comando==S_RIGTH){
        personaje.incrementXPos(MOVEMENT_QUANTITY_X);
        personaje.setTypeOfMoveSprite(S_RIGTH);
        personaje.setDirection(S_RIGTH);
    } else if (comando==S_LEFT){
        personaje.incrementXPos(-MOVEMENT_QUANTITY_X);
        personaje.setTypeOfMoveSprite(S_LEFT);
        personaje.setDirection(S_LEFT);
    } else if (comando==S_JUMP && !personaje.estaSaltando()){
        personaje.setEnSalto(true);
        personaje.setTypeOfMoveSprite(S_JUMP);
    } else if (comando==S_JUMP){
       // personaje.setTypeOfMoveSprite(S_FLAP);
    } else if (comando==S_DOWN){
        personaje.setTypeOfMoveSprite(S_DOWN);

    }else if (comando == S_STILL_RIGTH){
       personaje.setTypeOfMoveSprite(S_STILL_RIGTH);
    } else if (comando == S_STILL_LEFT){
        personaje.setTypeOfMoveSprite(S_STILL_LEFT);
    }

    //sendCompleteScene();  //comento nose si esta bien? tal vez deberia mandar siempre la escena completa
}

void GameLoop::weaponComand(uint8_t comando) {
    DuckPlayer& personaje = map_personajes[1];
    if (comando==S_PICKUP){
        
    } else if (comando==S_LEAVE_GUN){
        
    } else if (comando==S_SHOOT){

        Weapon& weapon = personaje.getWeapon();
        if (weapon.isEmptyAmmo()){
            return;
        }
        weapon.setXPos(personaje.getXPos());
        weapon.setYPos(personaje.getYPos());
        weapon.setDirection(personaje.getDirection());
        std::unique_ptr<Bullet> bullet = weapon.shoot();
        personaje.setXPos(weapon.getXPos());
        personaje.setYPos(weapon.getYPos());
        map_bullets.emplace(id_balas, std::move(bullet));
        id_balas++;


        
    }
}

void GameLoop::sendCompleteScene(){

    CommandGame command;
    command.type_of_action = S_FULL_GAME_BYTE;
    command.scene_id = S_SCENE_ID;
    


    for (auto& personaje : map_personajes) {
        if (!personaje.second.isAlive()) {
            continue;
        }
        DTODuck dto_duck = {personaje.first,personaje.second.getType(), personaje.second.getXPos(), personaje.second.getYPos(),
                            personaje.second.getTypeOfMoveSprite(), personaje.second.getWeapon().getType()};


       command.lista_patos.push_back(dto_duck);

    }
    for (auto& bullet : map_bullets) {
        DTOBullet dto_bullet = {bullet.first, bullet.second->getType(), bullet.second->getXPos(), bullet.second->getYPos(), bullet.second->getDirection()};
        command.lista_balas.push_back(dto_bullet);
    }

    for (auto& weapon : map_free_weapons) {
        DTOGuns dto_gun = {weapon.second.getType(), weapon.second.getXPos(), weapon.second.getYPos()};
        command.lista_guns.push_back(dto_gun);
    }


    queues_map.sendMessagesToQueues(command);

}

void GameLoop::paraCadaPatoAction() {
    for (auto& personaje : map_personajes) {
        personaje.second.executeAction();

    }
}


void GameLoop::checkCoalition(std::unique_ptr<Bullet>& bullet) {
    for (auto& personaje : map_personajes) {
        if (personaje.second.isAlive()) {
            if (personaje.second.getXPos() < bullet->getXPos()  &&
                personaje.second.getXPos() + DUCK_WIDTH > bullet->getXPos() &&
                personaje.second.getYPos() < bullet->getYPos() &&
                personaje.second.getYPos() + DUCK_HEIGHT > bullet->getYPos()) {
                personaje.second.applyDamage(100);
              }
                bullet->kill();
        }
        }

}

GameLoop::~GameLoop() {}
