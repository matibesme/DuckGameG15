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
        list_plataformas(),
        load_game_config(),
        duck_action(map_personajes, map_free_weapons, map_bullets, id_balas)
        {}

void GameLoop::run() {
    try {
        load_game_config.loadGame(list_plataformas);
        map_personajes.emplace(1, DuckPlayer(1, 1, POSICION_INICIAL_X, POSICION_INICIAL_Y));
        map_personajes.emplace(2, DuckPlayer(2, 2, 100, POSICION_INICIAL_Y));
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
    if (comando.type_of_action == MOVEMENT_ACTION) {
        duck_action.movementComand(comando.type_of_movement);
    } else if (comando.type_of_action == WEAPON_ACTION) {
        duck_action.weaponComand(comando.type_of_movement);
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



void GameLoop::sendCompleteScene(){
    GameState command;

    command.backGround_id = SCENE_ID;

    for (auto& platform : list_plataformas) {
        command.lista_plataformas.push_back(platform);
    }

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
        if (personaje.second.getWeapon().getType() == GRANADA_GUN && personaje.second.getWeapon().isActive()) {
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





GameLoop::~GameLoop() {}
