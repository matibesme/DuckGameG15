//
// Created by matibesme on 31/10/24.
//

#include "duck_action.h"


DuckAction::DuckAction(std::map<uint8_t, DuckPlayer>& map_personajes,
                       std::map<uint8_t,std::unique_ptr<Weapon>>& map_free_weapons,
                       std::map<uint16_t, std::unique_ptr<Bullet>>& map_bullets,
                       uint16_t& id_balas):
        map_personajes(map_personajes),
        map_free_weapons(map_free_weapons),
        map_bullets(map_bullets),
        id_balas(id_balas) {}


void DuckAction::movementComand(uint8_t comando) {
    DuckPlayer& personaje = map_personajes[1];

    switch (comando) {
        case S_RIGTH:
            personaje.incrementXPos(MOVEMENT_QUANTITY_X);
            personaje.setTypeOfMoveSprite(S_RIGTH);
            personaje.setDirection(S_RIGTH);
            break;
        case S_LEFT:
            personaje.incrementXPos(-MOVEMENT_QUANTITY_X);
            personaje.setTypeOfMoveSprite(S_LEFT);
            personaje.setDirection(S_LEFT);
            break;
        case S_JUMP:
            if (!personaje.estaSaltando()) {
                personaje.setEnSalto(true);
            } else if (personaje.getVelocidadY() < 0) {
                personaje.setFlapping(true);
                personaje.increaseFlappingCounter();
            }
            break;
        case S_DOWN:
            personaje.setTypeOfMoveSprite(S_DOWN);
            break;
        case S_STILL_RIGTH:
            personaje.setTypeOfMoveSprite(S_STILL_RIGTH);
            break;
        case S_STILL_LEFT:
            personaje.setTypeOfMoveSprite(S_STILL_LEFT);
            break;
        default:
            break;
    }

    // Check if the character is jumping or flapping when moving sideways
    if (personaje.isFlapping()) {
        personaje.setTypeOfMoveSprite(S_FLAP);
    } else if (personaje.estaSaltando()) {
        personaje.setTypeOfMoveSprite(S_JUMP);
    }
}

void DuckAction::weaponComand(uint8_t comando) {
    DuckPlayer& personaje = map_personajes[1];

    switch (comando) {
        case S_PICKUP:
            // Implement pickup logic here
            break;
        case S_LEAVE_GUN:
            // personaje.removeWeapon();
            break;
        case S_SHOOT:
            {
                Weapon& weapon = personaje.getWeapon();
                if (weapon.isEmptyAmmo()) {
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
            break;
        default:
            break;
    }
}
