#ifndef GUN_H
#define GUN_H

#include "SDL2pp/SDL2pp.hh"
#include "constant_definitons.h"
#include "Graficos.h"

using namespace SDL2pp;

class Gun{
private:
    Graficos& graficos;
    uint8_t typeOfGun;
    bool is_equiped;
    float pos_x;
    float pos_y;
    void setEquip(bool equip);
    void actualizarTextura(const char*& texture_equipped, const char*& texture_not_equipped);

public:
    Gun(Graficos& graficos, float pos_x, float pos_y, uint8_t typeOfGun);
    void draw(bool isFliped, SDL2pp::Renderer& renderer);
    bool isEquipped();
    void setGun(uint8_t gun);

    void update(float d, float d1);
};

#endif