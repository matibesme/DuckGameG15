#ifndef GUN_H
#define GUN_H

#include <SDL2pp/SDL2pp.hh>
#include "constant_definitons.h"
#include "Graficos.h"

class Gun{
private:
    float pos_x;
    float pos_y;
    //La implementación que debería ir es la comentada, pero para que sea más sencillo harcodear lo dejo así.
    //SDL2pp::Texture& texture_not_equipped;
    //SDL2pp::Texture& texture_equipped;
    SDL2pp::Texture texture_equipped;
    SDL2pp::Texture texture_not_equipped;
    const int height;
    const int width;
    uint8_t typeOfGun;

public:
    //Este es el constructor que va.
    //Gun(float initial_pos_x, float initial_pos_y, int height, int width, SDL2pp::Texture& texture_equipped, SDL2pp::Texture& texture_not_equipped);
    Gun(Graficos& graficos);
    void draw(SDL2pp::Renderer& renderer);
    void update_pos(float pos_x, float pos_y);
    bool isEquipped();
    void setGun(uint8_t gun);
};

#endif