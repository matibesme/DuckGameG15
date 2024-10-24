#ifndef BULLET_H
#define BULLET_H

#include "Graficos.h"
#include <SDL2pp/SDL2pp.hh>
#include "constant_definitons.h"

class Bullet {
private:
    SDL2pp::Texture texture;  // Textura de la bala
    float pos_x, pos_y;       // Posición de la bala
    int height, width;        // Dimensiones de la bala
    bool fliped;              // Si la bala está volteada o no

public:
    // Constructor
    Bullet(float initial_pos_x, float initial_pos_y, Graficos& graficos);

    // Dibuja la bala en su posición actual
    void draw(SDL2pp::Renderer& renderer);

    // Actualiza la posición de la bala con nuevos valores
    void update(float new_pos_x, float new_pos_y, uint8_t orientacion);

};

#endif  // BULLET_H
