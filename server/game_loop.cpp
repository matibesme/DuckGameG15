#include "game_loop.h"
#include "items/weapons/cowboy_pistol.h"
#include <bits/fs_fwd.h>
#include <bits/fs_path.h>
#include <items/weapons/duel_pistol.h>
#include <items/weapons/magnum.h>

//despues sacar
#include "items/weapons/banana.h"


GameLoop::GameLoop( std::shared_ptr<BlockingQueue<CommandClient>>& queue_comandos, bool& end_game,
                    std::shared_ptr<ProtectedQueuesMap>& queues_map):
        queue_comandos(queue_comandos),
        end_game(end_game),
        queues_map(queues_map),
        map_personajes(),
        respawn_weapon_points(),
        map_free_weapons(),
        factory_weapons(),
        map_bullets(),
        id_balas(1),
        id_weapons(),
        list_plataformas(),
        load_game_config(),
        duck_action(map_personajes, map_free_weapons, map_bullets, id_balas, id_weapons){}

void GameLoop::run() {
    try {
        load_game_config.loadGame(list_plataformas, respawn_weapon_points);


        map_personajes.emplace(1, DuckPlayer(1, 1, POSICION_INICIAL_X, POSICION_INICIAL_Y));
        uint8_t id = 0;
        for (auto& respawn : respawn_weapon_points) {

            map_free_weapons.emplace(id, factory_weapons.createWeapon(respawn.type, respawn.x_pos, respawn.y_pos));
            id++;
        }


        while (!end_game) {
            //hago mover el pato 2 de manera constante hacia la derecha
            /*DuckPlayer& personaje = map_personajes[2];
            personaje.incrementXPos(MOVEMENT_QUANTITY_X);
            personaje.setTypeOfMoveSprite(S_RIGTH);*/

            CommandClient comando;
            while (queue_comandos->try_pop(comando)) {
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
            checkCoalition(it->second);
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
        uint8_t weapon_type = NOGUN;
        if (personaje.second.isWeaponEquipped()) {
           weapon_type = personaje.second.getWeapon().getType();
        }
        DTODuck dto_duck = {personaje.first,personaje.second.getType(), personaje.second.getXPos(), personaje.second.getYPos(),
                            personaje.second.getTypeOfMoveSprite(), weapon_type};


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
    /*
    for (auto& box : list_boxes) {


    }*/
    queues_map->sendMessagesToQueues(command);
}

void GameLoop::paraCadaPatoAction() {
    for (auto& personaje : map_personajes) {
        bool is_on_platform = false;
        for (auto& platform : list_plataformas) {
            if ( personaje.second.getXPos() +15 >= platform.x_pos && personaje.second.getXPos()+DUCK_WIDTH-15 <= platform.x_pos + platform.width) {

                if (personaje.second.getYPos()+DUCK_HEIGHT==platform.y_pos|| (personaje.second.getYPos() + DUCK_HEIGHT > platform.y_pos &&  personaje.second.getYPos()+personaje.second.getVelocidadY() <= platform.y_pos)) {
                    if (personaje.second.getVelocidadY() < 0) {
                        personaje.second.stopJump(platform.y_pos-DUCK_HEIGHT);
                    } else
                    {
                        personaje.second.setYPos(platform.y_pos - DUCK_HEIGHT);
                    }
                    is_on_platform = true;
                }
            } else if (personaje.second.getYPos() + DUCK_HEIGHT -DUCK_HEIGHT/3> platform.y_pos  &&
        personaje.second.getYPos() < platform.y_pos + platform.height) {



                if (personaje.second.getXPos() + DUCK_WIDTH > platform.x_pos &&
                    personaje.second.getXPos() < platform.x_pos &&
                    personaje.second.getDirection() == RIGHT) {


                    personaje.second.setXPos(platform.x_pos - DUCK_WIDTH);
                    }


                else if (personaje.second.getXPos() < platform.x_pos + platform.width &&
                         personaje.second.getXPos() > platform.x_pos &&
                         personaje.second.getDirection() == LEFT) {
                    personaje.second.setXPos(platform.x_pos + platform.width);
                          }

        }

        }


        if (!is_on_platform && !personaje.second.estaSaltando()) {
            personaje.second.setEnSalto(true);
            personaje.second.setVelocidadY(0);

        }
        personaje.second.executeAction();
        if (!personaje.second.isWeaponEquipped()) continue;

        if (personaje.second.getWeapon().getType() == GRANADA_GUN && personaje.second.getWeapon().isActive()) {

            std::unique_ptr<Bullet> bullet = personaje.second.getWeapon().shoot();
            map_bullets.emplace(id_balas, std::move(bullet));
            id_balas++;
        }
    }
}

void GameLoop::checkCoalition(std::unique_ptr<Bullet>& bullet) {
    for (auto& plataform : list_plataformas) {
        bullet->colisionWithPlatform(plataform.x_pos, plataform.y_pos, plataform.width, plataform.height);
    }
    for (auto& wall )
}



GameLoop::~GameLoop() {}
