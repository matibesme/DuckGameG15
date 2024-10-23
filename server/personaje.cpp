#include "personaje.h"

Personaje::Personaje():  typeOfMove(S_STILL),saltando(false),velocidad(VELOCIDAD_INICIAL){}


float Personaje::getXPos() {
    return x_pos;
}

float Personaje::getYPos() {
    return y_pos;
}

uint8_t Personaje::getTypeOfMoveSprite() {
    return typeOfMove;
}

void Personaje::setXPos(float pos_x) {

    this->x_pos += pos_x;

    if (this->x_pos<0 ||this->x_pos>MAP_LIMIT_X ){
        this->x_pos=0;
    }
}

void Personaje::setYPos(float pos_y) {

    this->y_pos = pos_y;

    if (this->y_pos<0 ||this->y_pos>MAP_LIMIT_Y ){
        this->y_pos=0;
    }
}

void Personaje::setTypeOfMoveSprite(uint8_t orientation) {
    this->typeOfMove = orientation;
}

void Personaje::setEnSalto(bool enSalto) {
    this->saltando=enSalto;
}

bool Personaje::estaSaltando() {
    return this->saltando;
}

void Personaje::setVelocidadY(float nuevaVelocidad){
    this->velocidad = nuevaVelocidad;
}

float Personaje::getVelocidadY(){
    return this->velocidad;
}

void Personaje::executeAction() {
    float gravedad = GRAVEDAD;
    if (estaSaltando()) {
        this->y_pos=(getYPos() -getVelocidadY());


       setVelocidadY(getVelocidadY() - gravedad);


        if (getYPos() >= 386) {
            this->y_pos = 386;         // Aterriza en el suelo
            setEnSalto(false);         // Termina el salto
            setVelocidadY(20);         // Reinicia velocidad de salto
        }
    }
}

Personaje::~Personaje() {}

