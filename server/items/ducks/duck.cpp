#include "duck.h"
#include <iostream>

DuckPlayer::DuckPlayer(uint8_t type, uint8_t id, float x_pos, float y_pos)
        : Objeto(type, id, x_pos, y_pos),
        is_weapon_equiped(true),
        typeOfMove(S_STILL_RIGTH),
        saltando(false),
        velocidad(VELOCIDAD_INICIAL),
        life(100),
        is_alive(true),
        gravity(GRAVEDAD),
        weapon(S_COWBOY_GUN, 1, 0, 0, 5, 10,20,4),

        weapons_list()
        {
            weapons_list.push_back(weapon);
        }

uint8_t DuckPlayer::getTypeOfMoveSprite() {
    return typeOfMove;
}

void DuckPlayer::incrementXPos(float pos_x) {

    this->x_pos += pos_x;

    if (this->x_pos<0 ||this->x_pos>MAP_LIMIT_X ){
        this->x_pos=0;
    }
}


void DuckPlayer::setTypeOfMoveSprite(uint8_t orientation) {
    this->typeOfMove = orientation;
}

void DuckPlayer::setEnSalto(bool enSalto) {
    this->saltando=enSalto;
}

void DuckPlayer::setVelocidadY(float velocidad_) {
    this->velocidad = velocidad_;
}

float& DuckPlayer::getVelocidadY(){
    return this->velocidad;
}

void DuckPlayer::executeAction() {
    if (estaSaltando()) {
        y_pos -= velocidad;
        getWeapon().setYPos(y_pos);
        velocidad -= gravity;

        this->gravity= GRAVEDAD;
        if (y_pos >= S_POSICION_INICIAL_Y) {
            y_pos = S_POSICION_INICIAL_Y;
            this->saltando = false;
            this->velocidad = VELOCIDAD_INICIAL;
            typeOfMove = (direction == S_RIGTH) ? S_STILL_RIGTH : S_STILL_LEFT;
        }

    }

}

bool DuckPlayer::estaSaltando() {
    return this->saltando;
}

Weapon& DuckPlayer::getWeapon() {
    return weapons_list.front();
}

void DuckPlayer::unequippWeapon() {
    if (is_weapon_equiped) {
        is_weapon_equiped = false;
    }
}

void DuckPlayer::equippWeapon() {
    if (!is_weapon_equiped) {
        is_weapon_equiped = true;
    }
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




void DuckPlayer::setGravity(float gravity_){
    this->gravity = gravity_;
}

DuckPlayer::~DuckPlayer() {}

