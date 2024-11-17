//
// Created by matibesme on 31/10/24.
//
#include "duck_action.h"
#include <iostream>
#include <random>

#include "items/weapons/factory_weapons.h"

DuckAction::DuckAction(
    std::map<uint8_t, DuckPlayer> &map_personajes,
    std::map<uint16_t, std::shared_ptr<Weapon>> &map_free_weapons,
    std::map<uint16_t, RespawnPoint> &respawn_weapon_points,
    std::map<uint16_t, int> &time_weapon_last_respawn,
    std::map<uint16_t, std::unique_ptr<Bullet>> &map_bullets,
    uint16_t &id_balas, uint16_t &id_weapons,
    std::map<uint16_t, Protection> &map_defense,
    std::map<uint16_t, Protection> &respawn_defense_points,
    uint16_t &id_defense, std::map<uint16_t, int> &time_defense_last_respawn)
    : map_personajes(map_personajes), map_free_weapons(map_free_weapons),
      respawn_weapon_points(respawn_weapon_points),
      time_weapon_last_respawn(time_weapon_last_respawn),
      map_bullets(map_bullets), map_defense(map_defense),
      respawn_defense_points(respawn_defense_points),
      time_defense_last_respawn(time_defense_last_respawn),
      id_defense(id_defense), id_balas(id_balas), id_weapons(id_weapons), change_weapon_counter(COWBOY_GUN), change_weapon_pressed(false) {}

void DuckAction::movementComand(uint8_t comando, uint8_t id) {
  DuckPlayer &personaje = map_personajes[id];
  if (personaje.isSliding()) {
    return;
  }
  switch (comando) {
  case RIGHT:
    personaje.incrementXPos(MOVEMENT_QUANTITY_X);
    personaje.setTypeOfMoveSprite(RIGHT);
    personaje.setDirection(RIGHT);
    break;
  case LEFT:
    personaje.incrementXPos(-MOVEMENT_QUANTITY_X);
    personaje.setTypeOfMoveSprite(LEFT);
    personaje.setDirection(LEFT);
    break;
  case JUMP:
    if (!personaje.estaSaltando()) {
      personaje.setEnSalto(true);
    } else if (personaje.getVelocidadY() < 0) {
      personaje.setFlapping(true);
      personaje.increaseFlappingCounter();
    }
    break;
  case DOWN:
    personaje.setTypeOfMoveSprite(DOWN);
    break;
  case STILL_RIGHT:
    personaje.setTypeOfMoveSprite(STILL_RIGHT);
    break;
  case STILL_LEFT:
    personaje.setTypeOfMoveSprite(STILL_LEFT);
    break;
  default:
    break;
  }

  // Check if the character is jumping or flapping when moving sideways
  if (personaje.isFlapping()) {
    personaje.setTypeOfMoveSprite(FLAP);
  } else if (personaje.estaSaltando()) {
    personaje.setTypeOfMoveSprite(JUMP);
  }
}

void DuckAction::weaponComand(uint8_t comando, uint8_t id) {
    DuckPlayer &personaje = map_personajes[id];
    bool pick = false;

    switch (comando) {
        case PICKUP: {
            for (auto &free_weapon : map_free_weapons) {
                if (personaje.isWeaponEquipped())
                    break;
                if (inRangePickUp(free_weapon.second->getXPos(),
                                  free_weapon.second->getYPos(), HEIGHT_GUN, WIDTH_GUN,
                                  personaje)) {

                    personaje.pickUpWeapon(std::move(free_weapon.second));

                    if (respawn_weapon_points.find(free_weapon.first) !=
                        respawn_weapon_points.end()) {
                        RespawnPoint weapon = respawn_weapon_points[free_weapon.first];

                        respawn_weapon_points.emplace(id_weapons, weapon);
                        respawn_weapon_points.erase(free_weapon.first);

                        std::random_device rd;
                        std::mt19937 gen(rd());
                        std::uniform_int_distribution<> distrib(1, 10);
                        int random_addition = distrib(gen) * 800;

                        time_weapon_last_respawn.emplace(id_weapons, random_addition);
                        id_weapons++;
                    }

                    map_free_weapons.erase(free_weapon.first);
                    pick = true;
                    break;
                }
            }
            if (pick)
                return;

            for (auto &defense : map_defense) {
                if (defense.second.type == HELMET_EQUIPPED) {
                    if (personaje.getHelmet() == HELMET_EQUIPPED)
                        break;
                    if (inRangePickUp(defense.second.x_pos, defense.second.y_pos,
                                      HEIGHT_HELMET, WIDTH_HELMET, personaje)) {
                        personaje.setHelmet(HELMET_EQUIPPED);
                        map_defense.erase(defense.first);
                        pick = true;
                    }
                } else {
                    if (personaje.getArmor() == ARMOR_EQUIPPED)
                        break;
                    if (inRangePickUp(defense.second.x_pos, defense.second.y_pos,
                                      HEIGHT_ARMOR, WIDTH_ARMOR, personaje)) {

                        personaje.setArmor(ARMOR_EQUIPPED);
                        map_defense.erase(defense.first);
                        pick = true;
                    }
                }

                if (pick && respawn_defense_points.find(defense.first) !=
                                respawn_defense_points.end()) {
                    Protection defense_protection = respawn_defense_points[defense.first];

                    respawn_defense_points.emplace(id_defense, defense_protection);
                    respawn_defense_points.erase(defense.first);
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> distrib(1, 10);
                    int random_addition = distrib(gen) * 800;

                    time_defense_last_respawn.emplace(id_defense, random_addition);
                    id_defense++;
                    break;
                } else if (pick)
                    break;
            }

            break;
        }

        case LEAVE_GUN: {
            if (!personaje.isWeaponEquipped())
                return;
            map_free_weapons.emplace(id_weapons++, personaje.removeWeapon());
            break;
        }

        case SHOOT: {
            if (!personaje.isWeaponEquipped())
                return;
            Weapon &weapon = personaje.getWeapon();
            if (weapon.isEmptyAmmo())
                return;
            weapon.setXPos(personaje.getXPos());
            weapon.setYPos(personaje.getYPos());
            weapon.setDirection(personaje.getDirection());

            int bullet_count = (weapon.getType() == ESCOPETA_GUN)        ? 6
                               : (weapon.getType() == PEW_PEW_LASER_GUN) ? 3
                                                                         : 1;

            for (int i = 0; i < bullet_count; ++i) {
                std::unique_ptr<Bullet> bullet = weapon.shoot(personaje.isAimingUp());
                if (!bullet)
                    return;
                map_bullets.emplace(id_balas++, std::move(bullet));
                if (weapon.getType() == BANANA_GUN or weapon.getType() == GRANADA_GUN) {
                    personaje.eraseGun();
                }
            }
            personaje.setXPos(weapon.getXPos());
            personaje.setYPos(weapon.getYPos());
            break;
        }

        case STOP_SHOOT: {
            if (!personaje.isWeaponEquipped()) {
                return;
            }
            personaje.getWeapon().stopShooting();
            break;
        }

        case AIM_UP: {
            personaje.aimUp();
            break;
        }

        case STOP_AIM_UP: {
            personaje.stopAimUp();
            break;
        }

        case CHEAT_CHANGE_WEAPON: {
            changeWeaponCheat(personaje);
            break;
        }

        case CHEAT_STOP_CHANGE_WEAPON: {
            change_weapon_pressed = false;
            break;
        }

        default: {
            break;
        }
    }
}


bool DuckAction::inRangePickUp(float x_pos, float y_pos, float HEIGHT,
                               float WIDTH, DuckPlayer &personaje) {

  return personaje.getXPos() + DUCK_WIDTH >= x_pos &&
         personaje.getXPos() <= x_pos + WIDTH &&
         personaje.getYPos() + DUCK_HEIGHT >= y_pos &&
         personaje.getYPos() <= y_pos + HEIGHT;
}

void DuckAction::changeWeaponCheat(DuckPlayer &personaje) {
    if (change_weapon_pressed) {
        return;
    }
    change_weapon_pressed = true;
    personaje.eraseGun();
    FactoryWeapons factory_weapons;
    std::shared_ptr<Weapon> weapon = factory_weapons.createWeapon(change_weapon_counter, personaje.getXPos(), personaje.getYPos());
    personaje.pickUpWeapon(weapon);
    if (change_weapon_counter == LASER_RIFLE_GUN) {
        change_weapon_counter = COWBOY_GUN;
    } else if (change_weapon_counter == SNIPER_GUN) {
        change_weapon_counter = GRANADA_GUN;
    } else {
        change_weapon_counter++;
    }
}




