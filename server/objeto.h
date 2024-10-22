#ifndef ELEMENT_H
#define ELEMENT_H

#include <cstdint>

class Objeto {
protected:
    uint8_t type;  // tipo de elemento
    uint8_t id;    // identificador único
    float x_pos;   // posición en X
    float y_pos;   // posición en Y

public:
    Objeto();
    
    // Métodos getter
    float getXPos() const;
    float getYPos() const;
    uint8_t getId() const;

    // Métodos setter
    void setXPos(float pos_x);
    void setYPos(float pos_y);
    void setId(uint8_t new_id);

    virtual ~Objeto();
};

#endif // ELEMENT_H
