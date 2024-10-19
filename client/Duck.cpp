#include "Duck.h"
#include <SDL_image.h>

Duck::Duck(float initialX, float initialY)
        : positionX(initialX), positionY(initialY), yVelocity(0),
          isMovingRight(false), isMovingLeft(false), isJumping(false), isOnFloor(true), runPhase(-1), initialY(initialY) {}

void Duck::update(bool moveRight, bool moveLeft, bool jump, unsigned int frameDelta) {
    isMovingRight = moveRight;
    isMovingLeft = moveLeft;

    if (isMovingRight) {
        positionX += frameDelta * 0.2;
        runPhase = (SDL_GetTicks() / 100) % 6;
    } else if (isMovingLeft) {
        positionX -= frameDelta * 0.2;
        runPhase = (SDL_GetTicks() / 100) % 6;
    } else {
        runPhase = 0;
    }

    if (jump) {

        isJumping = true;
        isOnFloor = false;
        yVelocity = jumpVelocity;
    }

    if (isJumping) {
        positionY += yVelocity;
        yVelocity += gravity;

        // Verificar si toca el suelo
        if (positionY >= initialY || positionY < initialY - 80) {
            positionY = initialY;
            isJumping = false;
            yVelocity = 0;
            isOnFloor = true;
        }
    }
}

void Duck::draw(SDL2pp::Renderer& renderer, SDL2pp::Texture& sprites) {
    if (positionX > renderer.GetOutputWidth())
        positionX = -50;

    if (positionX < -50)
        positionX = renderer.GetOutputWidth();

    int src_x = 0, src_y = 6;

    if (isMovingRight || isMovingLeft) {
        src_x = 32 * runPhase;
    }

    if (isJumping) {
        src_y = 100;
    } else if (isOnFloor) {
        src_y = 70;
    }

    int vcenter = renderer.GetOutputHeight() / 1.1;
    SDL2pp::Rect destRect((int)positionX, (int)(vcenter - 50 - (initialY - positionY)), 50, 50);

    if (isMovingLeft) {
        renderer.Copy(sprites, SDL2pp::Rect(src_x, src_y, 32, 24), destRect, 0.0, SDL2pp::Point(0, 0), SDL_FLIP_HORIZONTAL);
    } else {
        renderer.Copy(sprites, SDL2pp::Rect(src_x, src_y, 32, 24), destRect);
    }
}

void Duck::setOnFloor(bool onFloor) {
    isOnFloor = onFloor;
}

float Duck::getPosition() const {
    return positionX;
}
