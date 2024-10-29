#include "duck.h"
#include <iostream>
#include <memory>
#include "../weapons/cowboy_pistol.h"


DuckPlayer::DuckPlayer(uint8_t type, uint8_t id, float x_pos, float y_pos)
    : Objeto(type, id, x_pos, y_pos),
      is_weapon_equiped(true),
      typeOfMove(S_STILL_RIGTH),
      saltando(false),
      velocidad(VELOCIDAD_INICIAL) // No es necesario inicializar weapons_list aquí
{
    // Agregando una nueva CowboyPistol a la lista de armas
    weapons_list.push_back(std::make_shared<CowboyPistol>(S_COWBOY_PISTOL, 1, 0, 0, 5, 250, 0, 0));
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
    float gravedad = GRAVEDAD;
    if (estaSaltando()) {
        y_pos = (y_pos - velocidad);
        getWeapon().setYPos(y_pos);

        setVelocidadY(velocidad - gravedad);

        if (y_pos >= S_POSICION_INICIAL_Y) {
            y_pos = S_POSICION_INICIAL_Y;
            setEnSalto(false);
            setVelocidadY(VELOCIDAD_INICIAL);
        }
    }
}

bool DuckPlayer::estaSaltando() {
    return this->saltando;
}

Weapon& DuckPlayer::getWeapon() {
    return *weapons_list.front();
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

DuckPlayer::~DuckPlayer() {}

