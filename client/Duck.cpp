#include "Duck.h"
#include <SDL_image.h>

const int SPRITE_ANIMATION_RATE = 100;
const int MAX_SPRITE_FRAMES = 6;
const int MAX_SPRITE_FRAMES_JUMP = 5;
const int SRC_Y_STANDING = 70;
const int SRC_Y_JUMPING = 40;
const int SRC_Y_MOVING = 6;
const int SPRITE_WIDTH = 32;
const int SPRITE_HEIGHT = 24;
const float VERTICAL_CENTER_DIVISOR = 1.1f;


Duck::Duck(float initialX, float initialY, Graficos& graficos)
        : positionX(initialX), positionY(initialY),
          isOnFloor(true), numSprite(0), initialY(initialY), gun(graficos),
          pixelDuckSpriteX(0), pixelDuckSpriteY(SRC_Y_MOVING), isFlipped(false),
          typeOfGun(C_NOGUN),
          sprites(graficos.LoadTexture(DATA_PATH "/whiteDuck.png")) {}

void Duck::update(float y_pos, float x_pos, uint8_t typeOfMove, uint8_t gunEquipped) {
    positionX = x_pos;
    positionY = y_pos;
    isFlipped = false;
    gun.setGun(gunEquipped);

    if(typeOfMove != STILL) {
        numSprite = (SDL_GetTicks() / SPRITE_ANIMATION_RATE) % MAX_SPRITE_FRAMES;
        if (typeOfMove == RIGTH) {
            pixelDuckSpriteX = SPRITE_WIDTH * numSprite;
        } else if (typeOfMove == LEFT) {
            pixelDuckSpriteX = SPRITE_WIDTH * numSprite;
            isFlipped = true;
        }
        else if (typeOfMove == JUMP) {
            pixelDuckSpriteY = SRC_Y_JUMPING;
            pixelDuckSpriteX = SPRITE_WIDTH * numSprite;
            numSprite = (SDL_GetTicks() / SPRITE_ANIMATION_RATE) % MAX_SPRITE_FRAMES_JUMP;
        } else if (typeOfMove == DOWN) {
            pixelDuckSpriteY = SRC_Y_STANDING;
        }
    }
}

void Duck::draw(SDL2pp::Renderer& renderer) {

    int vcenter = renderer.GetOutputHeight() / VERTICAL_CENTER_DIVISOR;
    Rect destRect((int)positionX, (int)(vcenter - DUCK_HEIGHT - (initialY - positionY)), DUCK_WIDTH, DUCK_HEIGHT);

    if (isFlipped) {
        renderer.Copy(sprites, Rect(pixelDuckSpriteX, pixelDuckSpriteY, SPRITE_WIDTH, SPRITE_HEIGHT), destRect, 0.0, Point(0, 0), SDL_FLIP_HORIZONTAL);
    } else {
        renderer.Copy(sprites, Rect(pixelDuckSpriteX, pixelDuckSpriteY, SPRITE_WIDTH, SPRITE_HEIGHT), destRect);
    }

    if(gun.isEquipped()){
        gun.update_pos(positionX + (2 * DUCK_WIDTH / 5), ((vcenter - DUCK_HEIGHT - (initialY - positionY))) + DUCK_HEIGHT / 2);
        gun.draw(isFlipped, renderer);
    }
}

bool Duck::checkCollision(SDL2pp::Rect rect) {
    Rect rectDuck((int)positionX, (int)positionY, DUCK_WIDTH, DUCK_HEIGHT);

    return (SDL_HasIntersection(&rectDuck, &rect));
}