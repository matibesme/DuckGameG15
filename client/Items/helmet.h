#ifndef HELMET_H
#define HELMET_H

#include "SDL2pp/SDL2pp.hh"
#include "constant_definitons.h"
#include "Graficos.h"

using namespace SDL2pp;

class Helmet {
private:
    Graficos& graficos;
    bool is_equipped;
    float pos_x;
    float pos_y;

public:
    Helmet(Graficos& graficos, float pos_x, float pos_y);
    void draw(bool isFliped, SDL2pp::Renderer& renderer);
    bool isEquipped();
    void equip();
    void unequip();
    void update(float new_x, float new_y);

    float getPosX();

    float getPosY();
};

#endif
