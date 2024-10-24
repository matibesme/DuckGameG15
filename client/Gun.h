#ifndef GUN_H
#define GUN_H

#include <SDL2pp/SDL2pp.hh>
#include "constant_definitons.h"
#include "Graficos.h"

using namespace SDL2pp;

class Gun{
private:
    Graficos& graficos;
    const int height;
    const int width;
    uint8_t typeOfGun;
    bool is_equiped;
    float pos_x;
    float pos_y;
    Texture texture_equipped;
    Texture texture_not_equipped;
    void setEquip(bool equip);
    void actualizarTextura();

public:
    Gun(Graficos& graficos);
    void draw(bool isFliped, SDL2pp::Renderer& renderer);
    void update_pos(float pos_x, float pos_y);
    bool isEquipped();
    void setGun(uint8_t gun);

};

#endif