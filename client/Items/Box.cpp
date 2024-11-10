#include "Box.h"
#include "common_constant.h"

#define IMAGE_BOX_WEAPON DATA_PATH "/objects/itemBox.png"
#define IMAGE_GRANADA_EXPLOTION DATA_PATH "/bullets/explode.png"
#define SOUND_GRANADA DATA_PATH "/sound/grenadeFire.wav"
#define SPRITE_WIDTH_BOX 32
#define SPRITE_HEIGHT_BOX 32
#define SPRITE_WIDTH_BULLET (384/6)
#define SPRITE_HEIGHT_BULLET 64

Box::Box(uint8_t id, float initial_pos_x, float initial_pos_y, Graficos& graficos)
        : graficos(graficos), idBox(id),
          pos_x(initial_pos_x), pos_y(initial_pos_y),
          typeOfAction(0), explosionSpriteX(-1), sound() {
  sound.inicializar();
}

void Box::draw(SDL2pp::Renderer& renderer) {
  const char* texture_path;
  SDL2pp::Rect area;
  SDL2pp::Rect destRect;

  if (typeOfAction == GRENADE_EXPLOSION) {
      texture_path = IMAGE_GRANADA_EXPLOTION;
      explosionSpriteX = (explosionSpriteX + 1);
      if (explosionSpriteX == 0) reproducirSonido();
      // destRect es el rectángulo donde se dibujará la textura
      destRect = SDL2pp::Rect((int)pos_x, (int)pos_y, WIDTH_GRENADE_EXPLOTION, HEIGHT_GRENADE_EXPLOTION);
      // area es el rectángulo que se tomará de la textura
      area = SDL2pp::Rect(explosionSpriteX * SPRITE_WIDTH_BULLET, 0, SPRITE_WIDTH_BULLET, SPRITE_HEIGHT_BULLET);

  } else {
      texture_path = IMAGE_BOX_WEAPON;
      // area: es el rectángulo que se toma de la textura
      area = SDL2pp::Rect(0, 0, SPRITE_WIDTH_BOX, SPRITE_HEIGHT_BOX);
      // destRect: es el rectángulo donde se dibujará la textura
      destRect = SDL2pp::Rect(pos_x, pos_y, WIDTH_BOX, HEIGHT_BOX);
  }

  // Cargar y copiar la textura
  Texture texture (graficos.LoadTexture(texture_path));
  renderer.Copy(texture, area, destRect);
}


void Box::update(uint8_t type_) {
    typeOfAction = type_;
}

uint8_t Box::getId() {
    return idBox;
}

void Box::reproducirSonido() {
    sound.reproducirEfecto(SOUND_GRANADA);
}
