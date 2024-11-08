#include "duck.h"
#include <iostream>
#include <memory>
#include "../weapons/cowboy_pistol.h"
#include "../weapons/duel_pistol.h"
#include "../weapons/magnum.h"
#include "../weapons/granada.h"
#include "../weapons/banana.h"
#include "../weapons/sniper.h"
#include "items/weapons/ak47.h"
#include "items/weapons/laser_rifle.h"
#include "items/weapons/pewpew_laser.h"
#include "items/weapons/shotgun.h"



DuckPlayer::DuckPlayer(): Objeto(0,0,0,0), is_weapon_equiped(false), typeOfMove(STILL_RIGHT), saltando(false),
                          velocidad(VELOCIDAD_INICIAL), life(100), is_alive(true), gravity(GRAVEDAD){}


DuckPlayer::DuckPlayer(uint8_t type, uint8_t id, float x_pos, float y_pos)
        : Objeto(type, id, x_pos, y_pos),
        is_weapon_equiped(true),
        typeOfMove(STILL_RIGHT),
        saltando(false),
        velocidad(VELOCIDAD_INICIAL),
        life(100),
        is_alive(true),
        gravity(GRAVEDAD),
        weapons_list(),
        counter_flapping(0),
        is_flapping(false)
    {

        // Agregando una nueva CowboyPistol a la lista de armas
        weapons_list.push_back(std::make_shared<CowboyPistol>(COWBOY_GUN, 1, 0, 0, 10, 38, 100, 0));

    }

uint8_t DuckPlayer::getTypeOfMoveSprite() {
    return typeOfMove;
}

void DuckPlayer::incrementXPos(float pos_x) {
    x_pos += pos_x;
    if (x_pos<0 ||x_pos>MAP_LIMIT_X ){
        x_pos=0;
    }
}


void DuckPlayer::setTypeOfMoveSprite(uint8_t orientation) {
    this->typeOfMove = orientation;
}

void DuckPlayer::setEnSalto(bool enSalto) {
    saltando=enSalto;
}

void DuckPlayer::setVelocidadY(float velocidad_) {
   velocidad = velocidad_;
}

float& DuckPlayer::getVelocidadY(){
    return velocidad;
}

void DuckPlayer::stopJump(float y_pos_ )
{
        counter_flapping = 0;
        y_pos = y_pos_;
        saltando = false;
        is_flapping = false;
        gravity = GRAVEDAD;
        velocidad = VELOCIDAD_INICIAL;
        typeOfMove = (direction == RIGHT) ? STILL_RIGHT : STILL_LEFT;

}

void DuckPlayer::executeAction() {
    if (saltando) {
        if (is_flapping) {
            gravity = GRAVITY_FLAP;
            counter_flapping--;

            if (counter_flapping == 0) {
                is_flapping = false;
                gravity = GRAVEDAD;
                typeOfMove= JUMP;
            }
        }
        y_pos -= velocidad;
        if (isWeaponEquipped()){
        getWeapon().setYPos(y_pos);
        }
        velocidad -= gravity;

        if (y_pos >= MAP_LIMIT_Y) {
            is_alive = false;
            stopJump(MAP_LIMIT_Y);
        }



    }
    if (is_weapon_equiped) {
        if (getWeapon().getReloadTime() != 0) {
            getWeapon().setReloadTime(getWeapon().getReloadTime() - 1);
        }
    }

}

bool DuckPlayer::estaSaltando() {
    return this->saltando;
}
/*
void DuckPlayer::setWeapon(Weapon& weapon) {
    
    weapons_list.push_back(std::make_shared<Weapon>(weapon));
    
}*/

Weapon& DuckPlayer::getWeapon() {
    return *weapons_list.front();
}

std::shared_ptr<Weapon> DuckPlayer::removeWeapon() {
    std::shared_ptr<Weapon> weapon = weapons_list.front();
    //retrnario si direction es right o left
     if (direction == RIGHT) {
        weapon->setXPos(x_pos+WIDTH_GUN );
    } else {
        weapon->setXPos(x_pos);
    }
    weapon->setYPos(y_pos+DUCK_HEIGHT-HEIGHT_GUN);

    weapons_list.pop_front();
    is_weapon_equiped = false;
    return weapon;
}

void DuckPlayer::pickUpWeapon(std::shared_ptr<Weapon> weapon) {
    weapons_list.push_back(weapon);
    is_weapon_equiped = true;
}

bool DuckPlayer::isWeaponEquipped() {
    return is_weapon_equiped;
}


bool DuckPlayer::isAlive() {
    return is_alive;
}

void DuckPlayer::applyDamage(uint8_t damage) {
    life -= damage;
    if (life <= 0) {
        is_alive = false;
    }
}

void DuckPlayer::setFlapping(bool flapping) {
    is_flapping = flapping;
}

bool DuckPlayer::isFlapping() {
    return is_flapping;
}

void DuckPlayer::increaseFlappingCounter() {
    if (counter_flapping == 0) {
        counter_flapping += CANT_FLAP;
        velocidad = -1;
    }
}

void DuckPlayer::setGravity(float gravity_){
    gravity = gravity_;
}




DuckPlayer::~DuckPlayer() {}

