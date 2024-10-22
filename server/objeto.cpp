#include "objeto.h"

// Constructor
Objeto::Objeto() : type(1), id(1), x_pos(0), y_pos(360) {}

// Métodos getter
float Objeto::getXPos() const {
    return x_pos;
}

float Objeto::getYPos() const {
    return y_pos;
}

uint8_t Objeto::getId() const {
    return id;
}

// Métodos setter
void Objeto::setXPos(float pos_x) {
    x_pos = pos_x;
}

void Objeto::setYPos(float pos_y) {
    y_pos = pos_y;
}

void Objeto::setId(uint8_t new_id) {
    this->id = new_id;
}

// Destructor
Objeto::~Objeto() {}
