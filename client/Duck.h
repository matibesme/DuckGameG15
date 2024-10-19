#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;
class Duck {
public:
    Duck(float initialX, float initialY);
    void update(bool moveRight, bool moveLeft, bool isJumping, unsigned int frameDelta);
    void draw(Renderer& renderer, Texture& sprites);
    void setOnFloor(bool onFloor);
    float getPosition() const;

private:
    float positionX;
    float positionY;
    float yVelocity;        // Velocidad vertical para el salto
    bool isMovingRight;
    bool isMovingLeft;
    bool isJumping;         // Controla si el pato está saltando
    bool isOnFloor;         // Controla si el pato está en el suelo
    int runPhase;
    const float gravity = 0.5f;
    const float jumpVelocity = -10.0f;  // Velocidad inicial del salto
    const float initialY;    // Mantiene la posición en Y inicial (suelo)
};

#endif // PLAYER_H
