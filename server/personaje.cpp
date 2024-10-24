#include "personaje.h"

Personaje::Personaje(uint8_t type, uint8_t id, float x_pos, float y_pos)
        : Objeto(type, id, x_pos, y_pos),
        is_weapon_equiped(true),
        typeOfMove(S_STILL),
        saltando(false),
        velocidad(VELOCIDAD_INICIAL),
        weapon(S_COWBOY_GUN, 1, 0, 0, 5, 10),
        weapons_list(){
            weapons_list.push_back(weapon);
        }


float& Personaje::getXPos() {
    return x_pos;
}

float& Personaje::getYPos() {
    return y_pos;
}

uint8_t& Personaje::getTypeOfMoveSprite() {
    return typeOfMove;
}

void Personaje::setXPos(float& pos_x) {

    this->x_pos += pos_x;

    if (this->x_pos<0 ||this->x_pos>MAP_LIMIT_X ){
        this->x_pos=0;
    }
}


void Personaje::setTypeOfMoveSprite(uint8_t& orientation) {
    this->typeOfMove = orientation;
}

void Personaje::setEnSalto(bool& enSalto) {
    this->saltando=enSalto;
}


void Personaje::setVelocidadY(float& nuevaVelocidad){
    this->velocidad = nuevaVelocidad;
}

float& Personaje::getVelocidadY(){
    return this->velocidad;
}

void Personaje::executeAction() {
    float gravedad = GRAVEDAD;
    if (estaSaltando()) {
        this->y_pos=(this->velocidad -getVelocidadY());


       this->velocidad=(this->velocidad - gravedad);


        if (getYPos() >= POSICION_INICIAL_Y) {
            this->y_pos = POSICION_INICIAL_Y;
            this->saltando=false;
            this->velocidad=  VELOCIDAD_INICIAL;
        }
    }
}




Weapon& Personaje::getWeapon() {
    return weapons_list.front();
}

void Personaje::unequippWeapon() {
    if (is_weapon_equiped) {
        is_weapon_equiped = false;
    }
}

void Personaje::equippWeapon() {
    if (!is_weapon_equiped) {
        is_weapon_equiped = true;
    }
}





Personaje::~Personaje() {}

