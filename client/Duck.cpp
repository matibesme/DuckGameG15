#include "Duck.h"
#include <SDL_image.h>

const float MOVE_SPEED = 0.2f;
const int SPRITE_ANIMATION_RATE = 100;
const int MAX_SPRITE_FRAMES = 6;
const int JUMP_SPRITE_INDEX = 2;
const float JUMP_VELOCITY_SCALE = 0.5f;
const int DUCK_WIDTH = 50;
const int DUCK_HEIGHT = 50;
const int SCREEN_WRAP_OFFSET = 50;
const int SRC_Y_STANDING = 70;
const int SRC_Y_JUMPING = 40;
const int SRC_Y_MOVING = 6;
const int SPRITE_WIDTH = 32;
const int SPRITE_HEIGHT = 24;
const float VERTICAL_CENTER_DIVISOR = 1.1f;
const int JUMP_LIMIT = 150;

Duck::Duck(float initialX, float initialY)
        : positionX(initialX), positionY(initialY),
          isMovingRight(false), isMovingLeft(false), isJumping(false), isOnFloor(true), colSprite(-1), initialY(initialY), tocoTecho(false) {}

void Duck::update(bool moveRight, bool moveLeft, bool jump, unsigned int frameDelta) {
    isMovingRight = moveRight;
    isMovingLeft = moveLeft;
    isJumping = jump;

    if (isMovingRight) {
        positionX += frameDelta * MOVE_SPEED;
        colSprite = (SDL_GetTicks() / SPRITE_ANIMATION_RATE) % MAX_SPRITE_FRAMES;
    } else if (isMovingLeft) {
        positionX -= frameDelta * MOVE_SPEED;
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
    }
}

void Duck::draw(SDL2pp::Renderer& renderer, SDL2pp::Texture& sprites) {
    if (positionX > renderer.GetOutputWidth())
        positionX = -SCREEN_WRAP_OFFSET;

    if (positionX < -SCREEN_WRAP_OFFSET)
        positionX = renderer.GetOutputWidth();

    int src_x = 0, src_y = SRC_Y_MOVING;

    if (isMovingRight || isMovingLeft) {
        src_x = SPRITE_WIDTH * colSprite;
    }

    if (isJumping) {
        src_y = SRC_Y_JUMPING;
        src_x = SPRITE_WIDTH * colSprite;
    } else if (isOnFloor) {
        src_y = SRC_Y_STANDING;
    }

    int vcenter = renderer.GetOutputHeight() / VERTICAL_CENTER_DIVISOR;
    Rect destRect((int)positionX, (int)(vcenter - DUCK_HEIGHT - (initialY - positionY)), DUCK_WIDTH, DUCK_HEIGHT);

    if (isMovingLeft) {
        renderer.Copy(sprites, Rect(src_x, src_y, SPRITE_WIDTH, SPRITE_HEIGHT), destRect, 0.0, Point(0, 0), SDL_FLIP_HORIZONTAL);
    } else {
        renderer.Copy(sprites, Rect(src_x, src_y, SPRITE_WIDTH, SPRITE_HEIGHT), destRect);
    }
}

void Duck::setOnFloor(bool onFloor) {
    isOnFloor = onFloor;
}

float Duck::getPosition() const {
    return positionX;
}

bool Duck::is_Jumping() const {
    return isJumping;
}

bool Duck::isOnTop() const {
    return positionY <= initialY - JUMP_LIMIT;
}

bool Duck::isTouchingFloor() const {
    return positionY == initialY;
}

void Duck::setPosicion(float x, float y) {
    positionX = x;
    positionY = y;
}

bool Duck::checkCollision(SDL2pp::Rect rect) {
    Rect rectDuck((int)positionX, (int)positionY, DUCK_WIDTH, DUCK_HEIGHT);

    return (SDL_HasIntersection(&rectDuck, &rect));
}
