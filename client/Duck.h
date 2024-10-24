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
    void update(float y_pos, float x_pos);
    void draw(Renderer& renderer, Texture& sprites, uint8_t typeOfMove);
    void setOnFloor(bool onFloor);
    float getPosition() const;
    bool is_Jumping() const;
    bool checkCollision(Rect rect);
    bool isTouchingFloor() const;
    bool isOnTop() const;
    void setPosicion(float x, float y);
    void setGunEquipped(bool is_equipped);

private:
    float positionX;
    float positionY;
    bool isMovingRight;
    bool isMovingLeft;
    bool isJumping;         // Controla si el pato está saltando
    bool isOnFloor;         // Controla si el pato está en el suelo
    int colSprite;
    const float jumpVelocity = -1.0f;  // Velocidad inicial del salto
    const float initialY;    // Mantiene la posición en Y inicial (suelo)
    bool tocoTecho;
    Gun gun;
};

#endif // PLAYER_H
