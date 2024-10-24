#include "personaje.h"

Personaje::Personaje(uint8_t type, uint8_t id, float x_pos, float y_pos)
        : Objeto(type, id, x_pos, y_pos), typeOfMove(S_STILL), saltando(false), velocidad(VELOCIDAD_INICIAL) {

}


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


        if (getYPos() >= POSICION_INICIAL_Y) {
            this->y_pos = POSICION_INICIAL_Y;
            setEnSalto(false);
            setVelocidadY(VELOCIDAD_INICIAL);
        }
    }
}




Personaje::~Personaje() {}

