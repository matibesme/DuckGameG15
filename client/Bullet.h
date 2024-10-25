#ifndef BULLET_H
#define BULLET_H

#include "Graficos.h"
#include <SDL2pp/SDL2pp.hh>
#include "constant_definitons.h"

class Bullet {
private:
    Graficos& graficos;      // Referencia a la clase Graficos
    float pos_x, pos_y;       // Posición de la bala
    int height, width;        // Dimensiones de la bala
    uint8_t orientationOfBullet;              // Si la bala está volteada o no
    void actualizarTipo(uint8_t bullet_type, const char*& texture);

public:
    // Constructor
    Bullet(float initial_pos_x, float initial_pos_y, Graficos& graficos, uint8_t orientacion);

    // Dibuja la bala en su posición actual
    void draw(SDL2pp::Renderer& renderer, uint8_t type);

    // Actualiza la posición de la bala con nuevos valores
    void update(float new_pos_x, float new_pos_y, uint8_t type, uint8_t orientacion);
};

#endif  // BULLET_H
