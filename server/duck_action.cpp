//
// Created by matibesme on 31/10/24.
//
#include "duck_action.h"
#include <iostream>

DuckAction::DuckAction(std::map<uint8_t, DuckPlayer>& map_personajes,
                       std::map<uint8_t,std::shared_ptr<Weapon>>& map_free_weapons,
                       std::map<uint16_t, std::unique_ptr<Bullet>>& map_bullets,
                       uint16_t& id_balas):
        map_personajes(map_personajes),
        map_free_weapons(map_free_weapons),
        map_bullets(map_bullets),
        id_balas(id_balas) {}


void DuckAction::movementComand(uint8_t comando) {
    DuckPlayer& personaje = map_personajes[1];

    switch (comando) {
        case RIGHT_J1:
            personaje.incrementXPos(MOVEMENT_QUANTITY_X);
            personaje.setTypeOfMoveSprite(RIGHT_J1);
            personaje.setDirection(RIGHT_J1);
            break;
        case LEFT_J1:
            personaje.incrementXPos(-MOVEMENT_QUANTITY_X);
            personaje.setTypeOfMoveSprite(LEFT_J1);
            personaje.setDirection(LEFT_J1);
            break;
        case JUMP_J1:
            if (!personaje.estaSaltando()) {
                personaje.setEnSalto(true);
            } else if (personaje.getVelocidadY() < 0) {
                personaje.setFlapping(true);
                personaje.increaseFlappingCounter();
            }
            break;
        case DOWN_J1:
            personaje.setTypeOfMoveSprite(DOWN_J1);
            break;
        case STILL_RIGHT_J1:
            personaje.setTypeOfMoveSprite(STILL_RIGHT_J1);
            break;
        case STILL_LEFT_J1:
            personaje.setTypeOfMoveSprite(STILL_LEFT_J1);
            break;
        default:
            break;
    }

    // Check if the character is jumping or flapping when moving sideways
    if (personaje.isFlapping()) {
        personaje.setTypeOfMoveSprite(FLAP_J1);
    } else if (personaje.estaSaltando()) {
        personaje.setTypeOfMoveSprite(JUMP_J1);
    }
}

void DuckAction::weaponComand(uint8_t comando) {
    DuckPlayer& personaje = map_personajes[1];
    Weapon& weapon = personaje.getWeapon();
    switch (comando) {
        case PICKUP_J1:
            // Implement pickup logic here

                if (personaje.isWeaponEquipped()) {
                    return;
                }
                for (auto& free_weapon : map_free_weapons) {
                    if (personaje.getXPos() + DUCK_WIDTH >= free_weapon.second->getXPos() &&
                        personaje.getXPos() <= free_weapon.second->getXPos() +WIDTH_GUN &&
                        personaje.getYPos() + DUCK_HEIGHT >= free_weapon.second->getYPos() &&
                        personaje.getYPos() <= free_weapon.second->getYPos() + HEIGHT_GUN) {

                        personaje.pickUpWeapon(std::move(free_weapon.second));
                        map_free_weapons.erase(free_weapon.first);
                        break;
                    }
                }
            break;
        case LEAVE_GUN_J1:
            // Implement leave gun logic here
            if (!personaje.isWeaponEquipped()) {
                return;
            }

            map_free_weapons.emplace(map_free_weapons.size() + 1, personaje.removeWeapon());
            break;
        case SHOOT_J1:
            {
            std::cout << "SHOOT" << std::endl;
            if (weapon.isEmptyAmmo()){
                return;
            }
            std::cout << "SHOOT AFUERA" << std::endl;
            weapon.setXPos(personaje.getXPos());
            weapon.setYPos(personaje.getYPos());
            weapon.setDirection(personaje.getDirection());
            if (weapon.getType() == ESCOPETA_GUN) {
                for (int i = 0; i < 6; i++) {

                    std::unique_ptr<Bullet> bullet = weapon.shoot();
                    if (bullet == nullptr) {
                        return;
                    }
                    map_bullets.emplace(id_balas, std::move(bullet));
                    id_balas++;
                }
                personaje.setXPos(weapon.getXPos());
                personaje.setYPos(weapon.getYPos());
            } else if (weapon.getType() == PEW_PEW_LASER_GUN) {
                for (int i = 0; i < 3; i++) {
                    std::unique_ptr<Bullet> bullet = weapon.shoot();
                    if (bullet == nullptr) {
                        return;
                    }
                    map_bullets.emplace(id_balas, std::move(bullet));
                    id_balas++;
                }
                personaje.setXPos(weapon.getXPos());
                personaje.setYPos(weapon.getYPos());
            } else {
                std::cout << "entro a la balas" << std::endl;
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
            break;
        case STOP_SHOOT_J1:
            weapon.stopShooting();
            break;
        default:
            break;
    }
}
