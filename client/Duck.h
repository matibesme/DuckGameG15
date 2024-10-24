#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2pp/SDL2pp.hh>
#include "constant_definitons.h"
#include "Gun.h"
#include "Graficos.h"
using namespace SDL2pp;
class Duck {
public:
    Duck(float initialX, float initialY, Graficos& graficos);
    void update(float y_pos, float x_pos, uint8_t typeOfMove, uint8_t gunEquipped);
    void draw(Renderer& renderer, Texture& sprites);
    bool checkCollision(Rect rect);

private:
    float positionX;
    float positionY;
    bool isMovingRight;
    bool isMovingLeft;
    bool isJumping;         // Controla si el pato está saltando
    bool isOnFloor;         // Controla si el pato está en el suelo
    int numSprite;
    const float initialY;    // Mantiene la posición en Y inicial (suelo)
    Gun gun;
    float pixelDuckSpriteX;
    float pixelDuckSpriteY;
    bool isFlipped;
    float pixelGunSpriteX;
    float pixelGunSpriteY;
    uint8_t typeOfGun;
};

#endif // PLAYER_H
