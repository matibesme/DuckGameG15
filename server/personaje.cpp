#include "personaje.h"

Personaje::Personaje(): x_pos(0), y_pos(386), typeOfMove(0) {}


float Personaje::getXPos() {
    return x_pos;
}

float Personaje::getYPos() {
    return y_pos;
}

uint8_t Personaje::getTypeOfMove() {
    return typeOfMove;
}

void Personaje::setXPos(float pos_x, bool isRight) {
    if (isRight) {
        this->x_pos += pos_x;
    } else {
        this->x_pos -= pos_x;
    }
    if (this->x_pos<0 ||this->x_pos>MAP_LIMIT_X ){
        this->x_pos=0;
    }
}

void Personaje::setYPos(float pos_y, bool isJump) {
    if (isJump) {
        this->y_pos -= pos_y;
    } else {
        this->y_pos += pos_y;
    }
    if (this->y_pos<0 ||this->y_pos>MAP_LIMIT_Y ){
        this->y_pos=0;
    }
}

void Personaje::setTypeOfMove(uint8_t orientation) {
    this->typeOfMove = orientation;
}

Personaje::~Personaje() {}

