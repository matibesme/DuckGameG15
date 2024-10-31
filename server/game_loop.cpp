#include "game_loop.h"
#include "items/weapons/cowboy_pistol.h"
#include <bits/fs_fwd.h>
#include <bits/fs_path.h>
#include <items/weapons/duel_pistol.h>
#include <items/weapons/magnum.h>
//despues sacar


GameLoop::GameLoop(BlockingQueue<CommandClient>& queue_comandos, bool& end_game,
                   ProtectedQueuesMap& queues_map):
        queue_comandos(queue_comandos),
        end_game(end_game),
        queues_map(queues_map),
        map_personajes(),
        map_free_weapons(),
        map_bullets(),
        id_balas(1),
        list_plataformas()
        {}

void GameLoop::run() {
    try {
        loadMap();
        sendBackground();
        map_personajes.emplace(1, DuckPlayer(1, 1, S_POSICION_INICIAL_X, S_POSICION_INICIAL_Y));
        map_personajes.emplace(2, DuckPlayer(2, 2, 100, S_POSICION_INICIAL_Y));
        /*
        list_free_weapons.emplace_back(CowboyPistol(S_COWBOY_GUN, 1, 100, 100, 10, 10, 10, 10));
        list_free_weapons.emplace_back(DuelPistol(S_PISTOLA_DUELOS_GUN, 2, 200, 200, 10, 10, 10, 10));
        list_free_weapons.emplace_back(Magnum(S_MAGNUM_GUN, 3, 300, 300, 10, 10, 10, 10));
         */

        while (!end_game) {
            //hago mover el pato 2 de manera constante hacia la derecha
            /*DuckPlayer& personaje = map_personajes[2];
            personaje.incrementXPos(MOVEMENT_QUANTITY_X);
            personaje.setTypeOfMoveSprite(S_RIGTH);*/

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
        //personaje.setTypeOfMoveSprite(S_JUMP);
    } else if (comando==S_JUMP && personaje.getVelocidadY() < 0 ){
        personaje.setFlapping(true);
        personaje.increaseFlappingCounter();
        //personaje.setTypeOfMoveSprite(S_FLAP);
    } else if (comando==S_DOWN){
        personaje.setTypeOfMoveSprite(S_DOWN);
    }else if (comando == S_STILL_RIGTH){
       personaje.setTypeOfMoveSprite(S_STILL_RIGTH);
    } else if (comando == S_STILL_LEFT){
        personaje.setTypeOfMoveSprite(S_STILL_LEFT);
    }

    //compruebo si esta saltando o flapeando en caso de que se mueva hacia los costados
    if(personaje.isFlapping()){
        personaje.setTypeOfMoveSprite(S_FLAP);
    }else if(personaje.estaSaltando()){
        personaje.setTypeOfMoveSprite(S_JUMP);
    }

    //sendCompleteScene();  //comento nose si esta bien? tal vez deberia mandar siempre la escena completa
}

void GameLoop::weaponComand(uint8_t comando) {
    DuckPlayer& personaje = map_personajes[1];
    if (comando==S_PICKUP){

    } else if (comando==S_LEAVE_GUN){
       // personaje.removeWeapon();
        
    } else if (comando==S_SHOOT){

        Weapon& weapon = personaje.getWeapon();
        if (weapon.isEmptyAmmo()){
            return;
        }
        weapon.setXPos(personaje.getXPos());
        weapon.setYPos(personaje.getYPos());
        weapon.setDirection(personaje.getDirection());
        std::unique_ptr<Bullet> bullet = weapon.shoot();
        if (bullet == nullptr) {
            return;
        }
        personaje.setXPos(weapon.getXPos());
        personaje.setYPos(weapon.getYPos());
        map_bullets.emplace(id_balas, std::move(bullet));
        id_balas++;
    }
}

void GameLoop::sendCompleteScene(){
    GameState command;
    command.scene_id = S_BACKGROUND_BYTE;

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
        DTOGuns dto_gun = {weapon.second->getType(), weapon.second->getXPos(), weapon.second->getYPos()};
        command.lista_guns.push_back(dto_gun);
    }
    queues_map.sendMessagesToQueues(command);
}

void GameLoop::paraCadaPatoAction() {
    for (auto& personaje : map_personajes) {
        personaje.second.executeAction();
        if (personaje.second.getWeapon().getType() == S_GRANADA_GUN && personaje.second.getWeapon().isActive()) {
            std::unique_ptr<Bullet> bullet = personaje.second.getWeapon().shoot();
            map_bullets.emplace(id_balas, std::move(bullet));
            id_balas++;
        }
    }
}

void GameLoop::checkCoalition(std::unique_ptr<Bullet>& bullet) {
    for (auto& personaje : map_personajes) {

        if (personaje.second.isAlive()) {
            if (personaje.second.getXPos() == bullet->getXPos()) {
                personaje.second.applyDamage(100);
                bullet->kill();
            }
        }
    }
}

//void GameLoop::checkCoalitionWithPlatform(DuckPlayer& personaje) {
    //for (auto& platform : list_plataformas) {
        //if (personaje.getXPos() >= platform.x_pos && personaje.getXPos() <= platform.x_pos + platform.width) {
           // if (personaje.getYPos()+ <= platform.y_pos && personaje.getYPos() <= platform.y_pos + platform.height) {
                //personaje.setEnSalto(true);

                //personaje.setVelocidadY(0);
            //}
        //}
    //}
//}


void GameLoop::loadMap() {


    YAML::Node map = YAML::LoadFile("../server/configuration/map.yaml");

    S_POSICION_INICIAL_X= map["duck"][0]["x"].as<float>();
    S_POSICION_INICIAL_Y= map["duck"][0]["y"].as<float>();
    S_LIFE= map["duck"][0]["life"].as<uint8_t>();
    S_RESPAWN_WEAPON_X= map["respawn_weapons_point"][0]["x"].as<float>();
    S_RESPAWN_WEAPON_Y= map["respawn_weapons_point"][0]["y"].as<float>();


    for (const auto& platform : map["platforms"]) {
        list_plataformas.emplace_back(DTOPlatform{platform["type"].as<uint8_t>(),
                                                  platform["x"].as<float>(), platform["y"].as<float>(),
                                                  platform["width"].as<float>(), platform["height"].as<float>()});
    }

}


void GameLoop::sendBackground() {
    GameState command;
    command.scene_id = S_SCENE_ID;
    for (auto& platform : list_plataformas) {
        command.lista_plataformas.push_back(platform);
    }
    queues_map.sendMessagesToQueues(command);
}


GameLoop::~GameLoop() {}
