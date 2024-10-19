#include "Duck.h"
#include <SDL_image.h>

Duck::Duck(float initialX, [[maybe_unused]]  float initialY)
        : positionX(initialX), runPhase(-1), isMovingRight(false), isMovingLeft(false), isOnFloor(false){}

void Duck::update(bool moveRight, bool moveLeft, unsigned int frameDelta) {
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
}

void Duck::draw(SDL2pp::Renderer& renderer, SDL2pp::Texture& sprites) {
    if (positionX > renderer.GetOutputWidth())
        positionX = -50;

    if (positionX < -50)
        positionX = renderer.GetOutputWidth();

    int src_x = 0, src_y = 6;
    if (isMovingRight || isMovingLeft) {
        src_x = 32 * runPhase;
    } else if (isOnFloor) {
        src_y = 70;
    }

    int vcenter = renderer.GetOutputHeight() / 1.1;
    SDL2pp::Rect destRect((int)positionX, vcenter - 50, 50, 50);

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
