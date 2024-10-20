#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;
class Duck {
public:
    Duck(float initialX, float initialY);
    void update(bool moveRight, bool moveLeft, bool jump, unsigned int frameDelta);
    void draw(Renderer& renderer, Texture& sprites);
    void setOnFloor(bool onFloor);
    float getPosition() const;
    bool is_Jumping() const;
    bool checkCollision(Rect rect);
    bool isTouchingFloor() const;
    bool isOnTop() const;

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

};

#endif // PLAYER_H
