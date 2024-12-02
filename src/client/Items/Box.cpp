#include "Box.h"

#include "common_constant.h"
#include "constantTextures.h"

#define SOUND_GRANADA DATA_PATH "/sound/grenadeFire.wav"
#define SPRITE_WIDTH_BOX 32
#define SPRITE_HEIGHT_BOX 32
#define SPRITE_WIDTH_BULLET (384 / 6)
#define SPRITE_HEIGHT_BULLET 64

Box::Box(uint8_t id, float initial_pos_x, float initial_pos_y,
         Graficos &graficos)
    : graficos(graficos), idBox(id), pos_x(initial_pos_x), pos_y(initial_pos_y),
      typeOfAction(0), explosionSpriteX(-1), sound() {
  Sound::inicializar();
}

void Box::draw(SDL2pp::Renderer &renderer) {
  const char *texture_path;
  SDL2pp::Rect area;
  SDL2pp::Rect destRect;

  if (typeOfAction == GRENADE_EXPLOSION) {
    texture_path = IMAGE_GRANADA_EXPLOTION;
    explosionSpriteX = (explosionSpriteX + 1);
    if (explosionSpriteX == 0)
      reproducirSonido();
    // destRect es el rectángulo donde se dibujará la textura
    destRect = SDL2pp::Rect((int)pos_x, (int)pos_y, WIDTH_GRENADE_EXPLOTION,
                            HEIGHT_GRENADE_EXPLOTION);
    // area es el rectángulo que se tomará de la textura
    area = SDL2pp::Rect(explosionSpriteX * SPRITE_WIDTH_BULLET, 0,
                        SPRITE_WIDTH_BULLET, SPRITE_HEIGHT_BULLET);

  } else {
    texture_path = IMAGE_BOX_WEAPON;
    // area: es el rectángulo que se toma de la textura
    area = SDL2pp::Rect(0, 0, SPRITE_WIDTH_BOX, SPRITE_HEIGHT_BOX);
    // destRect: es el rectángulo donde se dibujará la textura
    destRect = SDL2pp::Rect(pos_x, pos_y, WIDTH_BOX, HEIGHT_BOX);
  }

  // Cargar y copiar la textura
  Texture &texture = graficos.getTexture(texture_path);
  renderer.Copy(texture, area, destRect);
}

void Box::update(uint8_t type_) { typeOfAction = type_; }

float Box::getX() { return pos_x; }

float Box::getY() { return pos_y; }

void Box::reproducirSonido() { sound.reproducirEfecto(SOUND_GRANADA); }
