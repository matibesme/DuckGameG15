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


Duck::Duck(float x_pos, float y_pos, uint8_t typeOfMove, uint8_t gunEquipped, uint8_t direction,Graficos& graficos)
        : positionX(x_pos), positionY(y_pos), graficos(graficos),
          numSprite(0), gun(graficos, positionX + (2 * DUCK_WIDTH / 5), positionY + DUCK_HEIGHT / 2, gunEquipped),
          isFlipped(false), typeOfGun(gunEquipped), pixelDuckSpriteX(0), pixelDuckSpriteY(SRC_Y_MOVING) {

    gun.setGun(gunEquipped);  // Configura el arma al inicializar el pato

    if(typeOfMove == STILL_LEFT){
        isFlipped = true;
    }
    if (direction != LEFT) {
        isFlipped = false;
    } else{
        isFlipped = true;
    }

    if (typeOfMove != STILL_RIGTH && typeOfMove != STILL_LEFT) {
        numSprite = (SDL_GetTicks() / SPRITE_ANIMATION_RATE) % MAX_SPRITE_FRAMES;

        if (typeOfMove == RIGTH) {
            pixelDuckSpriteX = SPRITE_WIDTH * numSprite;
            pixelDuckSpriteY = SRC_Y_MOVING;
            isFlipped = false;
        } else if (typeOfMove == LEFT) {
            pixelDuckSpriteX = SPRITE_WIDTH * numSprite;
            pixelDuckSpriteY = SRC_Y_MOVING;
            isFlipped = true;
        } else if (typeOfMove == JUMP) {
            pixelDuckSpriteY = SRC_Y_JUMPING;
            pixelDuckSpriteX = SPRITE_WIDTH * numSprite;
            numSprite = (SDL_GetTicks() / SPRITE_ANIMATION_RATE) % MAX_SPRITE_FRAMES_JUMP;

        } else if (typeOfMove == DOWN) {
            pixelDuckSpriteY = SRC_Y_STANDING;
            pixelDuckSpriteX = SPRITE_WIDTH;
        }
    }
}

void Duck::draw(SDL2pp::Renderer& renderer) {
/*
    const char* texture_path;
    actualizarTipo(texture_path);

    Texture texture (graficos.LoadTexture(texture_path));
*/
    Texture texture (graficos.LoadTexture(DATA_PATH "/whiteDuck.png"));
    Rect destRect((int)positionX, positionY, DUCK_WIDTH, DUCK_HEIGHT);

    if (isFlipped) {
        renderer.Copy(texture, Rect(pixelDuckSpriteX, pixelDuckSpriteY, SPRITE_WIDTH, SPRITE_HEIGHT), destRect, 0.0, Point(0, 0), SDL_FLIP_HORIZONTAL);
    } else {
        renderer.Copy(texture, Rect(pixelDuckSpriteX, pixelDuckSpriteY, SPRITE_WIDTH, SPRITE_HEIGHT), destRect);
    }

    if(gun.isEquipped()){
        gun.draw(isFlipped, renderer);
    }
}

void Duck::actualizarTipo(const char*& texture) {
    switch (typeOfGun) {
        case C_NOGUN:
            texture = DATA_PATH "/whiteDuck.png";
            break;
        case C_COWBOY_GUN:
            texture = DATA_PATH "/whiteDuck.png";
            break;
    }
}

bool Duck::checkCollision(SDL2pp::Rect rect) {
    Rect rectDuck((int)positionX, (int)positionY, DUCK_WIDTH, DUCK_HEIGHT);

    return (SDL_HasIntersection(&rectDuck, &rect));
}
