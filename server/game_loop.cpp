#include "game_loop.h"
#include "items/weapons/cowboy_pistol.h"
#include <bits/fs_fwd.h>
#include <bits/fs_path.h>
#include <items/weapons/duel_pistol.h>
#include <items/weapons/magnum.h>

//despues sacar
#include "items/weapons/banana.h"


GameLoop::GameLoop( std::shared_ptr<BlockingQueue<CommandClient>>& queue_comandos, bool& end_game,
                    std::shared_ptr<ProtectedQueuesMap>& queues_map, std::list<uint8_t>& list_id_clientes):
        list_id_clientes(list_id_clientes),
        queue_comandos(queue_comandos),
        end_game(end_game),
        queues_map(queues_map),
        map_personajes(),
        respawn_weapon_points(),
        time_weapon_last_respawn(),
        map_free_weapons(),
        factory_weapons(),
        map_bullets(),
        id_balas(0),
        id_weapons(0),
        id_boxes(0),
        id_defense(0),
        list_plataformas(),
        map_helmet(),
        map_armor(),
        respawn_defense_points(),
        time_defense_last_respawn(),
        duck_action(map_personajes, map_free_weapons, respawn_weapon_points, time_weapon_last_respawn,
            map_bullets, id_balas, id_weapons, map_helmet,map_armor, respawn_defense_points, id_defense),
        list_colors({"red","blue","green","yellow","pink","purple","orange","brown","black","white"}),
        load_game_config(factory_weapons, list_plataformas, respawn_weapon_points, map_helmet, map_armor, respawn_defense_points,id_defense,
            id_weapons, id_boxes,map_free_weapons, list_boxes, map_bullets, id_balas)
        {}

void GameLoop::run() {
    try {
        load_game_config.loadGame();

        for (auto& id : list_id_clientes) {
            map_personajes.emplace(id, DuckPlayer(0, id, POSICION_INICIAL_X, POSICION_INICIAL_Y, "red"));

        }


        while (!end_game) {


            CommandClient comando;
            while (queue_comandos->try_pop(comando)) {
                checkCommand(comando);

            }
            paraCadaPatoAction();
            checkBullets();
            respawnWeapon();
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
        duck_action.movementComand(comando.type_of_movement,comando.id);
    } else if (comando.type_of_action == WEAPON_ACTION) {
        duck_action.weaponComand(comando.type_of_movement,comando.id);
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
        DTODuck dto_duck = {personaje.first,personaje.second.getColor(), personaje.second.getXPos(), personaje.second.getYPos(),
                                personaje.second.getTypeOfMoveSprite(), weapon_type, personaje.second.getHelmet(), personaje.second.getArmor(), personaje.second.isAimingUp(), personaje.second.getDirection()};


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

    for (auto& box : list_boxes) {
        DTOBoxes dto_box = {box.getId(), box.getXPos(), box.getYPos()};
        command.lista_boxes.push_back(dto_box);

    }

    for (auto& helmet : map_helmet) {

        command.lista_helmets.push_back(helmet.second);
    }

    for (auto& armor : map_armor) {
        command.lista_armors.push_back(armor.second);
    }

    queues_map->sendMessagesToQueues(command);
}

void GameLoop::paraCadaPatoAction() {
    for (auto& personaje : map_personajes) {
        
        checkCoalitionDuckPlatform(personaje.second);
        personaje.second.executeAction();
        if (!personaje.second.isWeaponEquipped()) continue;

        if (personaje.second.getWeapon().getType() == GRANADA_GUN && personaje.second.getWeapon().isActive()) {

            std::unique_ptr<Bullet> bullet = personaje.second.getWeapon().shoot(personaje.second.isAimingUp());
            map_bullets.emplace(id_balas, std::move(bullet));
            id_balas++;
        }
    }
}

void GameLoop::checkCoalition(std::unique_ptr<Bullet>& bullet) {
    for (auto& plataform : list_plataformas) {
        bullet->colisionWithPlatform(plataform.x_pos, plataform.y_pos, plataform.width, plataform.height);
    }
    for (auto& character : map_personajes) {
        bool colision = bullet->colisionWithDuck(character.second.getXPos(), character.second.getYPos(), DUCK_WIDTH, DUCK_HEIGHT);
        if (colision) {
            character.second.applyDamage(bullet->getDamage());
            return;
        }
    }
    for (auto it = list_boxes.begin(); it != list_boxes.end(); ) {
        bool colision = bullet->colisionWithBox(it->getXPos(), it->getYPos(), WIDTH_BOX, HEIGHT_BOX);
        if (colision) {
            it->takeDamage(bullet->getDamage());
            if (it->isDestroyed()) {
                it = list_boxes.erase(it);
                break;
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }
}

void GameLoop::checkCoalitionDuckPlatform(DuckPlayer& personaje) {
    bool is_on_platform = false;
    for (auto& platform : list_plataformas) {

        if (personaje.getXPos() + 15 >= platform.x_pos && personaje.getXPos() + DUCK_WIDTH - 15 <= platform.x_pos + platform.width) {
        //caso plataformas inferior y superior
            if (personaje.getYPos() + DUCK_HEIGHT == platform.y_pos || 
                (personaje.getYPos() + DUCK_HEIGHT > platform.y_pos && personaje.getYPos() + personaje.getVelocidadY() <= platform.y_pos)) {
                if (personaje.getVelocidadY() < 0) {
                    personaje.stopJump(platform.y_pos - DUCK_HEIGHT);
                } else {
                    personaje.setYPos(platform.y_pos - DUCK_HEIGHT);
                }
                is_on_platform = true;
            } else if (personaje.getYPos() <= platform.y_pos + platform.height &&
                       personaje.getYPos() + DUCK_HEIGHT > platform.y_pos + platform.height &&
                       personaje.getVelocidadY() > 0) {
                personaje.setYPos(platform.y_pos + platform.height);
                personaje.setVelocidadY(0);
            }
        } else if (personaje.getYPos() + DUCK_HEIGHT - DUCK_HEIGHT / 3 > platform.y_pos &&
                   personaje.getYPos() < platform.y_pos + platform.height) {
        //caso paredes de plataformas
           if (personaje.getXPos() + DUCK_WIDTH > platform.x_pos &&
                personaje.getXPos() < platform.x_pos &&
                personaje.getDirection() == RIGHT) {
                personaje.setXPos(platform.x_pos - DUCK_WIDTH);
            } else if (personaje.getXPos() < platform.x_pos + platform.width &&
                       personaje.getXPos() > platform.x_pos &&
                       personaje.getDirection() == LEFT) {
                personaje.setXPos(platform.x_pos + platform.width);
            }
        }
    }

    if (!is_on_platform && !personaje.estaSaltando()) {
        personaje.setEnSalto(true);
        personaje.setVelocidadY(0);
    }
}


void GameLoop::respawnWeapon()
{

    for (auto& time: time_weapon_last_respawn) {
            if (time.second ==0) {
                RespawnPoint& weapon = respawn_weapon_points[time.first];
                map_free_weapons.emplace(time.first, factory_weapons.createWeapon(weapon.type, weapon.x_pos, weapon.y_pos));
                time_weapon_last_respawn.erase(time.first);

            } else {
                time_weapon_last_respawn[time.first]--;
            }

    }


}

GameLoop::~GameLoop() {}
