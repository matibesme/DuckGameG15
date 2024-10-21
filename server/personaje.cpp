#include "personaje.h"

Personaje::Personaje(): x_pos(0), y_pos(386), orientation(0) {}


float Personaje::getXPos() {
    return x_pos;
}

float Personaje::getYPos() {
    return y_pos;
}

uint8_t Personaje::getOrientation() {
    return orientation;
}

void Personaje::setXPos(float x_pos, bool isRight) {
    if (isRight) {
        this->x_pos += x_pos;
    } else {
        this->x_pos -= x_pos;
    }
}

void Personaje::setYPos(float y_pos, bool isJump) {
    if (isJump) {
        this->y_pos -= y_pos;
    } else {
        this->y_pos += y_pos;
    }
}

void Personaje::setTypeOfMove(uint8_t orientation) {
    this->orientation = orientation;
}

Personaje::~Personaje() {}

