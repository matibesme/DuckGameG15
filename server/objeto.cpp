#include "objeto.h"
#include "constant_definitons.h"

// Constructor
Objeto::Objeto(uint8_t type, uint8_t id,float x_pos, float y_pos)
    :type(type), id(id), x_pos(x_pos), y_pos(y_pos) {}

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
    this->y_pos = pos_y;

    if (this->y_pos<POSICION_INICIAL_X ||this->y_pos>MAP_LIMIT_Y ){
        this->y_pos=POSICION_INICIAL_X;
    }
}

void Objeto::setId(uint8_t new_id) {
    this->id = new_id;
}




// Destructor
Objeto::~Objeto() {}
