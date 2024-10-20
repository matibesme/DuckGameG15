#include "Duck.h"
#include <SDL_image.h>

Duck::Duck(float initialX, float initialY)
        : positionX(initialX), positionY(initialY),
          isMovingRight(false), isMovingLeft(false), isJumping(false), isOnFloor(true), colSprite(-1), initialY(initialY), goDown(false) {}

void Duck::update(bool moveRight, bool moveLeft, bool jump, bool go_Down, unsigned int frameDelta) {
    isMovingRight = moveRight;
    isMovingLeft = moveLeft;
    isJumping = jump;
    goDown = go_Down;

    if (isMovingRight) {
        positionX += frameDelta * 0.2;
        colSprite = (SDL_GetTicks() / 100) % 6;
    } else if (isMovingLeft) {
        positionX -= frameDelta * 0.2;
        colSprite = (SDL_GetTicks() / 100) % 6;

    }
    if(goDown) {
        positionY -= jumpVelocity * frameDelta * .33;

        if (positionY >= initialY) {
            positionY = initialY;
            goDown = false;
        }
    } else if (isJumping) {
        if (positionY >= initialY - 150) {
            colSprite = 2;
            isOnFloor = false;
            positionY += jumpVelocity * frameDelta * 1;
        }else{
            isJumping = false;
            goDown = true;
        }
    }
    else {
        colSprite = 0;
    }
}

void Duck::draw(SDL2pp::Renderer& renderer, SDL2pp::Texture& sprites) {
    if (positionX > renderer.GetOutputWidth())
        positionX = -50;

    if (positionX < -50)
        positionX = renderer.GetOutputWidth();

    int src_x = 0, src_y = 6;

    if (isMovingRight || isMovingLeft) {
        src_x = 32 * colSprite;
    }

    if (isJumping) {
        src_y = 40;
        src_x = 32 * colSprite;
    } else if (isOnFloor) {
        src_y = 70;
    }

    int vcenter = renderer.GetOutputHeight() / 1.1;
    Rect destRect((int)positionX, (int)(vcenter - 50 - (initialY - positionY)), 50, 50);

    if (isMovingLeft) {
        renderer.Copy(sprites, Rect(src_x, src_y, 32, 24), destRect, 0.0, Point(0, 0), SDL_FLIP_HORIZONTAL);
    } else {
        renderer.Copy(sprites, Rect(src_x, src_y, 32, 24), destRect);
    }
}

void Duck::setOnFloor(bool onFloor) {
    isOnFloor = onFloor;
}

float Duck::getPosition() const {
    return positionX;
}

bool Duck::is_Jumping() {
    return isJumping && positionY < initialY - 150;
}

bool Duck::isGoDown() {
    return goDown;
}

bool Duck::checkCollision(SDL2pp::Rect rect){
    Rect rectDuck((int)positionX, (int)positionY, 50, 50);

    return (SDL_HasIntersection(&rectDuck, &rect));
}