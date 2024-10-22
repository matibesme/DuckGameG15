#include "element.h"

// Constructor
Element::Element() : x_pos(0), y_pos(386) {}

// Métodos getter
float Element::getXPos() const {
    return x_pos;
}

float Element::getYPos() const {
    return y_pos;
}

uint8_t Element::getId() const {
    return id;
}

// Métodos setter
void Element::setXPos(float pos_x) {
    x_pos = pos_x;
}

void Element::setYPos(float pos_y) {
    y_pos = pos_y;
}

void Element::setId(uint8_t id) {
    this->id = id;
}

// Destructor
Element::~Element() {}
