#ifndef ARMOR_H
#define ARMOR_H

#include "SDL2pp/SDL2pp.hh"
#include "../common/common_constant.h"
#include "Graficos.h"

using namespace SDL2pp;

class Armor {
private:
    Graficos& graficos;
    bool is_equipped;
    float pos_x;
    float pos_y;
    void setEquip(bool equip);

public:
    Armor(Graficos& graficos, float pos_x, float pos_y);
    void draw(bool isFliped, SDL2pp::Renderer& renderer, bool isOnGround, bool isOnDuck);
    void update(float new_x, float new_y);

    float getPosX();

    float getPosY();
};

#endif
