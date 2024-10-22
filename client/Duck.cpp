#include "Duck.h"
#include <SDL_image.h>

const int SPRITE_ANIMATION_RATE = 100;
const int MAX_SPRITE_FRAMES = 6;
const int DUCK_WIDTH = 50;
const int DUCK_HEIGHT = 50;
const int SRC_Y_STANDING = 70;
const int SRC_Y_JUMPING = 40;
const int SRC_Y_MOVING = 6;
const int SPRITE_WIDTH = 32;
const int SPRITE_HEIGHT = 24;
const float VERTICAL_CENTER_DIVISOR = 1.1f;


Duck::Duck(float initialX, float initialY)
        : positionX(initialX), positionY(initialY),
          isOnFloor(true), colSprite(0), initialY(initialY), tocoTecho(false) {}

void Duck::update(float y_pos, float x_pos) {
    positionX = x_pos;
    positionY = y_pos;
    colSprite = (SDL_GetTicks() / SPRITE_ANIMATION_RATE) % MAX_SPRITE_FRAMES;
    /*
    if (isMovingRight) {
        positionX += frameDelta * MOVE_SPEED;
        colSprite = (SDL_GetTicks() / SPRITE_ANIMATION_RATE) % MAX_SPRITE_FRAMES;
    } else if (isMovingLeft) {
        //positionX -= frameDelta * MOVE_SPEED;
        positionX -= frameDelta * 0.2f;
        colSprite = (SDL_GetTicks() / SPRITE_ANIMATION_RATE) % MAX_SPRITE_FRAMES;
    }

    if (isOnTop()) {
        tocoTecho = true;
    }

    if (isJumping && !tocoTecho) {
        colSprite = JUMP_SPRITE_INDEX;
        isOnFloor = false;
        positionY += jumpVelocity * frameDelta * JUMP_VELOCITY_SCALE;
    } else {
        isJumping = false;
        positionY -= jumpVelocity * frameDelta * JUMP_VELOCITY_SCALE;
        if (positionY >= initialY) {
            positionY = initialY;
            tocoTecho = false;
        }
    }*/
}

void Duck::draw(SDL2pp::Renderer& renderer, SDL2pp::Texture& sprites, uint8_t typeOfMove) {
    int src_x = 0, src_y = SRC_Y_MOVING;
    if(typeOfMove != STILL) {
        if (typeOfMove == RIGTH || typeOfMove == LEFT) {
            src_x = SPRITE_WIDTH * colSprite;
        }
        if (typeOfMove == JUMP) {
            src_y = SRC_Y_JUMPING;
            src_x = SPRITE_WIDTH * colSprite;
        } else if (typeOfMove == DOWN) {
            src_y = SRC_Y_STANDING;
        }
    }

    int vcenter = renderer.GetOutputHeight() / VERTICAL_CENTER_DIVISOR;
    Rect destRect((int)positionX, (int)(vcenter - DUCK_HEIGHT - (initialY - positionY)), DUCK_WIDTH, DUCK_HEIGHT);

    if (typeOfMove==LEFT) {
        renderer.Copy(sprites, Rect(src_x, src_y, SPRITE_WIDTH, SPRITE_HEIGHT), destRect, 0.0, Point(0, 0), SDL_FLIP_HORIZONTAL);
    } else {
        renderer.Copy(sprites, Rect(src_x, src_y, SPRITE_WIDTH, SPRITE_HEIGHT), destRect);
    }
}

bool Duck::isTouchingFloor() const {
    return positionY == initialY;
}

bool Duck::checkCollision(SDL2pp::Rect rect) {
    Rect rectDuck((int)positionX, (int)positionY, DUCK_WIDTH, DUCK_HEIGHT);

    return (SDL_HasIntersection(&rectDuck, &rect));
}
