

Personaje::Personaje(): x_pos(30), y_pos(30), orientation(0) {}




uint16_t Personaje::getXPos() {
    return x_pos;
}

uint16_t Personaje::getYPos() {
    return y_pos;
}

uint8_t Personaje::getOrientation() {
    return orientation;
}

void Personaje::setXPos(uint16_t x_pos) {
    this->x_pos += x_pos;
}

void Personaje::setYPos(uint16_t y_pos) {
    this->y_pos += y_pos;
}

void Personaje::setOrientation(uint8_t orientation) {
    this->orientation = orientation;
}


