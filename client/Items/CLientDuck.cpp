#include "ClientDuck.h"
#include <SDL_image.h>

#define IMAGE_DUCK DATA_PATH "/Duck.png"
const int SPRITE_ANIMATION_RATE = 120;
const int MAX_SPRITE_FRAMES = 6;
const int MAX_SPRITE_FRAMES_JUMP = 5;
const int SRC_Y_STANDING = 70;
const int SRC_Y_JUMPING = 40;
const int SRC_Y_MOVING = 6;
const int SPRITE_WIDTH = 32;
const int SPRITE_HEIGHT = 24;
const float VERTICAL_CENTER_DIVISOR = 1.1f;


ClientDuck::ClientDuck(uint8_t id, float x_pos, float y_pos, uint8_t gunEquipped, uint8_t typeOfMove, Graficos& graficos)
        : idDuck(id), positionX(x_pos), positionY(y_pos), graficos(graficos),
          numSprite(0), gun(graficos, positionX + (2 * DUCK_WIDTH / 5), positionY + DUCK_HEIGHT / 2, gunEquipped),
          isFlipped(false), typeOfGun(gunEquipped), pixelDuckSpriteX(0), pixelDuckSpriteY(SRC_Y_MOVING),
          coloredTexture(nullptr), armor(graficos, positionX , positionY), helmet(graficos, positionX, positionY)
{
    update(y_pos, x_pos, typeOfMove, gunEquipped);
}

void ClientDuck::update(float y_pos, float x_pos, uint8_t typeOfMove, uint8_t gunEquipped) {
    positionX = x_pos;
    positionY = y_pos;
    gun.setGun(gunEquipped);

    if(typeOfMove == STILL_LEFT){
        isFlipped = true;
    }

    if (typeOfMove != STILL_RIGHT && typeOfMove != STILL_LEFT) {
        numSprite = (SDL_GetTicks() / SPRITE_ANIMATION_RATE) % MAX_SPRITE_FRAMES;

        if (typeOfMove == RIGHT) {
            pixelDuckSpriteX = SPRITE_WIDTH * numSprite;
            pixelDuckSpriteY = SRC_Y_MOVING;
            isFlipped = false;
        } else if (typeOfMove == LEFT) {
            pixelDuckSpriteX = SPRITE_WIDTH * numSprite;
            pixelDuckSpriteY = SRC_Y_MOVING;
            isFlipped = true;
        } else if (typeOfMove == JUMP) {
            pixelDuckSpriteY = SRC_Y_JUMPING;
            pixelDuckSpriteX = SPRITE_WIDTH;

        }else if (typeOfMove == FLAP) {
            pixelDuckSpriteY = SRC_Y_JUMPING;
            numSprite = (SDL_GetTicks() / SPRITE_ANIMATION_RATE) % MAX_SPRITE_FRAMES_JUMP;
            // Limitar numSprite entre 3 y 4
            numSprite = std::clamp(numSprite, 3, 4);
            // Calcular la posición del sprite
            pixelDuckSpriteX = SPRITE_WIDTH * numSprite;
        } else if (typeOfMove == DOWN) {
            pixelDuckSpriteY = SRC_Y_STANDING;
            pixelDuckSpriteX = 0;
        }
    } else {
        pixelDuckSpriteX = 0;
        pixelDuckSpriteY = SRC_Y_MOVING;
    }
}

void ClientDuck::draw(Renderer& renderer) {
    // Si aún no se ha aplicado el color, llamamos a applyColor
    if (!coloredTexture) {
        applyColor(renderer);
    }

    // destRect es el rectángulo donde se dibujará el pato
    SDL2pp::Rect destRect((int)positionX, (int)positionY, DUCK_WIDTH, DUCK_HEIGHT);
    // srcRect es el rectángulo que se tomará de la textura
    SDL2pp::Rect srcRect(pixelDuckSpriteX, pixelDuckSpriteY, SPRITE_WIDTH, SPRITE_HEIGHT);

    // Dibujar el pato con el color modificado y la dirección correspondiente
    if (isFlipped) {
        renderer.Copy(*coloredTexture, srcRect, destRect, 0.0, SDL2pp::Point(0, 0), SDL_FLIP_HORIZONTAL);
    } else {
        renderer.Copy(*coloredTexture, srcRect, destRect);
    }

    //dibujo la armadura completa siempre por ahora
    helmet.update(positionX, positionY);
    helmet.draw(isFlipped, renderer);
    armor.update(positionX, positionY);
    armor.draw(isFlipped, renderer);

    // Dibujar el arma si está equipada
    if (gun.isEquipped()) {
        gun.update(positionX + (2 * DUCK_WIDTH/ 5), positionY + DUCK_HEIGHT / 2);
        gun.draw(isFlipped, renderer);
    }
}

void ClientDuck::applyColor(Renderer& renderer) {
    SDL_Surface* loadedSurface = IMG_Load((IMAGE_DUCK));

    SDL2pp::Surface surface(loadedSurface);

    Uint32 white = SDL_MapRGB(surface.Get()->format, 255, 255, 255);
    Uint8 r = 255, g = 255, b = 255;

    switch (idDuck % 4) {
        case 0: r = 255; g = 0; b = 0; break;     // Rojo dominante
        case 1: r = 0; g = 0; b = 255; break;     // Azul dominante
        case 2: r = 139; g = 69; b = 19; break;   // Marrón dominante
        case 3: r = 138; g = 43; b = 226; break;  // Violeta dominante
    }

    for (int y = 0; y < surface.Get()->h; ++y) {
        for (int x = 0; x < surface.Get()->w; ++x) {
            Uint32* pixel = (Uint32*)((Uint8*)surface.Get()->pixels + y * surface.Get()->pitch + x * surface.Get()->format->BytesPerPixel);
            if (*pixel == white) {
                *pixel = SDL_MapRGB(surface.Get()->format, r, g, b);
            }
        }
    }

    coloredTexture = std::make_unique<SDL2pp::Texture>(renderer, surface);
}

uint8_t ClientDuck::getId() const {
    return idDuck;
}

int ClientDuck::getPosX() {
    return positionX;
}

int ClientDuck::getPosY() {
    return positionY;
}
