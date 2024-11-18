#include "ClientDuck.h"

#include <SDL_image.h>

#define IMAGE_DUCK DATA_PATH "/objects/Duck.png"
const int SPRITE_ANIMATION_RATE = 120;
const int MAX_SPRITE_FRAMES = 6;
const int MAX_SPRITE_FRAMES_JUMP = 5;
const int SRC_Y_STANDING = 70;
const int SRC_Y_JUMPING = 40;
const int SRC_Y_MOVING = 6;
const int SPRITE_WIDTH = 32;
const int SPRITE_HEIGHT = 24;
const float VERTICAL_CENTER_DIVISOR = 1.1f;

ClientDuck::ClientDuck(uint8_t id, float x_pos, float y_pos,
                       uint8_t gunEquipped, uint8_t typeOfMove,
                       std::string color, Graficos &graficos)
    : idDuck(id), positionX(x_pos), positionY(y_pos), graficos(graficos),
      numSprite(0), gun(graficos, positionX + (2 * DUCK_WIDTH / 5),
                        positionY + DUCK_HEIGHT / 2, gunEquipped),
      isFlipped(false), typeOfGun(gunEquipped), pixelDuckSpriteX(0),
      pixelDuckSpriteY(SRC_Y_MOVING), coloredTexture(nullptr),
      armor(graficos, positionX, positionY),
      helmet(graficos, positionX, positionY), armorEquipped(false),
      helmetEquipped(false), isOnGround(false), isLookingUp(false) {
  applyColor(graficos.GetRenderer(), color);
  update(y_pos, x_pos, typeOfMove, gunEquipped, armorEquipped, helmetEquipped,
         false, RIGHT);
}

void ClientDuck::update(float y_pos, float x_pos, uint8_t typeOfMove,
                        uint8_t gunEquipped, uint8_t armor_, uint8_t helmet_,
                        bool lookingUp, uint8_t orientacion) {
  isOnGround = false;
  isLookingUp = lookingUp;
  positionX = x_pos;
  positionY = y_pos;
  typeOfGun = gunEquipped;

  if (typeOfMove == STILL_LEFT)
    isFlipped = true;

  if (armor_ == ARMOR_EQUIPPED)
    armorEquipped = true;
  else
    armorEquipped = false;

  if (helmet_ == HELMET_EQUIPPED)
    helmetEquipped = true;
  else
    helmetEquipped = false;

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
      if (orientacion == RIGHT)
        isFlipped = false;
      else
        isFlipped = true;

      pixelDuckSpriteY = SRC_Y_JUMPING;
      pixelDuckSpriteX = SPRITE_WIDTH;

    } else if (typeOfMove == FLAP) {
      if (orientacion == RIGHT)
        isFlipped = false;
      else
        isFlipped = true;
      pixelDuckSpriteY = SRC_Y_JUMPING;
      numSprite =
          (SDL_GetTicks() / SPRITE_ANIMATION_RATE) % MAX_SPRITE_FRAMES_JUMP;
      // Limitar numSprite entre 3 y 4
      numSprite = std::clamp(numSprite, 3, 4);
      // Calcular la posición del sprite
      pixelDuckSpriteX = SPRITE_WIDTH * numSprite;
    } else if (typeOfMove == DOWN) {
      pixelDuckSpriteY = SRC_Y_STANDING;
      pixelDuckSpriteX = 0;
      isOnGround = true;
    }
  } else {
    pixelDuckSpriteX = 0;
    pixelDuckSpriteY = SRC_Y_MOVING;
  }
}

void ClientDuck::draw(Renderer &renderer) {
  // destRect es el rectángulo donde se dibujará el pato
  SDL2pp::Rect destRect((int)positionX, (int)positionY, DUCK_WIDTH,
                        DUCK_HEIGHT);
  // srcRect es el rectángulo que se tomará de la textura
  SDL2pp::Rect srcRect(pixelDuckSpriteX, pixelDuckSpriteY, SPRITE_WIDTH,
                       SPRITE_HEIGHT);

  // Dibujar el pato con el color modificado y la dirección correspondiente
  if (isFlipped) {
    renderer.Copy(*coloredTexture, srcRect, destRect, 0.0, SDL2pp::Point(0, 0),
                  SDL_FLIP_HORIZONTAL);
  } else {
    renderer.Copy(*coloredTexture, srcRect, destRect);
  }

  if (helmetEquipped) {
    helmet.update(positionX, positionY);
    helmet.draw(isFlipped, renderer, isOnGround, true);
  }
  if (armorEquipped) {
    armor.update(positionX, positionY);
    armor.draw(isFlipped, renderer, isOnGround, true);
  }

  // Dibujar el arma si está equipada
  gun.drawOnDuck(positionX + (2 * DUCK_WIDTH / 5), positionY + DUCK_HEIGHT / 2,
                 isFlipped, typeOfGun, isLookingUp, renderer);
}

void ClientDuck::applyColor(SDL2pp::Renderer &renderer,
                            const std::string &color) {
  SDL_Surface *loadedSurface = IMG_Load(IMAGE_DUCK);
  if (!loadedSurface) {
    throw std::runtime_error("Failed to load duck image");
  }

  SDL2pp::Surface surface(loadedSurface);

  // Defino el color del pato a partir del mapa de colores
  auto colorDuck = colorMap[color];

  // Bloqueo la superficie para manipular los píxeles directamente
  SDL_LockSurface(loadedSurface);

  // Itero sobre cada píxel de la superficie
  Uint32 *pixels = (Uint32 *)loadedSurface->pixels;
  int totalPixels = loadedSurface->w * loadedSurface->h;

  Uint32 whitePixel =
      SDL_MapRGB(loadedSurface->format, 255, 255, 255); // Color blanco original
  Uint32 newColor = SDL_MapRGBA(loadedSurface->format, colorDuck.r, colorDuck.g,
                                colorDuck.b, colorDuck.a);

  for (int i = 0; i < totalPixels; ++i) {
    if (pixels[i] == whitePixel) {
      pixels[i] = newColor; // Cambia solo el blanco al nuevo color
    }
  }

  // Desbloqueo la superficie tras modificar los píxeles
  SDL_UnlockSurface(loadedSurface);

  // Aplico el color modificado a la textura
  coloredTexture = std::make_unique<SDL2pp::Texture>(renderer, surface);
}

uint8_t ClientDuck::getId() const { return idDuck; }

int ClientDuck::getPosX() { return positionX; }

int ClientDuck::getPosY() { return positionY; }

ClientDuck::~ClientDuck() {
  // La textura se libera automáticamente porque es un std::unique_ptr
  coloredTexture.reset();
}
