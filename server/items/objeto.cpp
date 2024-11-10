#include "objeto.h"

// Constructor
Objeto::Objeto(uint8_t type, uint8_t id, float x_pos, float y_pos):
        type(type), id(id), x_pos(x_pos), y_pos(y_pos), direction(RIGHT) {}

// Métodos getter
float Objeto::getXPos() const { return x_pos; }

float Objeto::getYPos() const { return y_pos; }

uint8_t Objeto::getType() const { return this->type; }

uint8_t Objeto::getId() const { return id; }

// Métodos setter
void Objeto::setXPos(float pos_x) { x_pos = pos_x; }

void Objeto::setYPos(float pos_y) { this->y_pos = pos_y; }

void Objeto::setId(uint8_t new_id) { this->id = new_id; }

uint8_t Objeto::getDirection() const { return direction; }

void Objeto::setDirection(uint8_t new_direction) { this->direction = new_direction; }

// Destructor
Objeto::~Objeto() {}
