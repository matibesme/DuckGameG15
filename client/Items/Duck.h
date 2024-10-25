#ifndef PLAYER_H
#define PLAYER_H

#include "SDL2pp/SDL2pp.hh"
#include "constant_definitons.h"
#include "Gun.h"
#include "Graficos.h"
using namespace SDL2pp;
class Duck {
public:
    Duck(float initial_pos_x, float initial_pos_y, uint8_t typeOfMove, uint8_t typeOfGun,uint8_t direction,
        Graficos& graficos);
    //void update(float y_pos, float x_pos, uint8_t typeOfMove, uint8_t gunEquipped);
    void draw(Renderer& renderer);
    bool checkCollision(Rect rect);

private:
    float positionX;
    float positionY;
    Graficos& graficos;
    int numSprite;
    Gun gun;
    bool isFlipped;
    uint8_t typeOfGun;
    float pixelDuckSpriteX;
    float pixelDuckSpriteY;
    void actualizarTipo(const char*& texture);
};

#endif // PLAYER_H
