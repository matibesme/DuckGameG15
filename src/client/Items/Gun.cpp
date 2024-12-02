#include "Gun.h"

#include "constantTextures.h"
#include <SDL_render.h>

Gun::Gun(Graficos &graficos, float pos_x, float pos_y, uint8_t typeOfGun)
    : graficos(graficos), posX(pos_x), posY(pos_y), typeGun(typeOfGun) {}

void Gun::drawOnDuck(float newX, float newY, bool isFliped, uint8_t gun,
                     bool lookingUp, SDL2pp::Renderer &renderer) {
  const char *texture_equipped = nullptr;
  const char *texture_not_equipped = nullptr;
  typeGun = gun;
  if (typeGun == NOGUN) {
    return;
  }
  posX = newX;
  posY = newY;
  actualizarTextura(texture_equipped, texture_not_equipped);
  auto &active_texture = graficos.getTexture(texture_equipped);

  // si esta flippeado dibujo a todas por igual
  if (isFliped) {
    if (lookingUp) {
      renderer.Copy(active_texture, SDL2pp::NullOpt,
                    Rect(posX - DUCK_WIDTH / 2.5, posY - DUCK_HEIGHT / 2.5,
                         WIDTH_GUN, HEIGHT_GUN),
                    90.0, SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
    } else {
      renderer.Copy(active_texture, SDL2pp::NullOpt,
                    Rect(posX - DUCK_WIDTH / 2.5, posY, WIDTH_GUN, HEIGHT_GUN),
                    0.0, SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
    }
  } else if (lookingUp) {
    renderer.Copy(
        active_texture, SDL2pp::NullOpt,
        Rect(posX + 3, posY - DUCK_HEIGHT / 2.5, WIDTH_GUN, HEIGHT_GUN), 90.0,
        SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
  } else if (typeGun == GRANADA_GUN || typeGun == BANANA_GUN) {
    renderer.Copy(active_texture, SDL2pp::NullOpt,
                  Rect(posX + 5, posY, WIDTH_GUN, HEIGHT_GUN));
  } else {
    renderer.Copy(active_texture, SDL2pp::NullOpt,
                  Rect(posX, posY, WIDTH_GUN, HEIGHT_GUN));
  }
}

void Gun::drawOnSpawn(SDL2pp::Renderer &renderer) {
  const char *texture_equipped = nullptr;
  const char *texture_not_equipped = nullptr;
  if (typeGun == NOGUN) {
    return;
  }
  actualizarTextura(texture_equipped, texture_not_equipped);
  auto &active_texture = graficos.getTexture(texture_not_equipped);

  if (typeGun == BANANA_GUN) {
    // destRect es el rectángulo donde se dibujará el pato
    SDL2pp::Rect destRect(posX, posY, WIDTH_GUN, HEIGHT_GUN);
    // srcRect es el rectángulo que se tomará de la textura
    SDL2pp::Rect srcRect(0, 32, 16, 16);
    renderer.Copy(active_texture, srcRect, destRect);
  } else {
    renderer.Copy(active_texture, SDL2pp::NullOpt,
                  Rect(posX, posY, WIDTH_GUN, HEIGHT_GUN));
  }
}

float Gun::getPosX() { return posX; }

float Gun::getPosY() { return posY; }

void Gun::actualizarTextura(const char *&texture_path_equipped,
                            const char *&texture_path_not_equipped) {
    // Mapa de tipos de arma a las rutas de texturas
    static const std::map<uint8_t, std::pair<const char*, const char*>> gunTextures = {
            {COWBOY_GUN, {IMAGE_COWBOY_GUN_EQUIPPED, IMAGE_COWBOY_GUN}},
            {AK47_GUN, {IMAGE_AK47_GUN_EQUIPPED, IMAGE_AK47_GUN}},
            {PISTOLA_DUELOS_GUN, {IMAGE_PISTOLA_DUELOS_GUN_EQUIPPED, IMAGE_PISTOLA_DUELOS_GUN}},
            {MAGNUM_GUN, {IMAGE_MAGNUM_GUN_EQUIPPED, IMAGE_MAGNUM_GUN}},
            {ESCOPETA_GUN, {IMAGE_ESCOPETA_GUN_EQUIPPED, IMAGE_ESCOPETA_GUN}},
            {SNIPER_GUN, {IMAGE_SNIPER_GUN_EQUIPPED, IMAGE_SNIPER_GUN}},
            {GRANADA_GUN, {IMAGE_GRANADA_GUN_EQUIPPED, IMAGE_GRANADA_GUN}},
            {BANANA_GUN, {IMAGE_BANANA_GUN_EQUIPPED, IMAGE_BANANA_GUN}},
            {PEW_PEW_LASER_GUN, {IMAGE_PEW_PEW_LASER_GUN_EQUIPPED, IMAGE_PEW_PEW_LASER_GUN}},
            {LASER_RIFLE_GUN, {IMAGE_LASER_RIFLE_GUN_EQUIPPED, IMAGE_LASER_RIFLE_GUN}},
    };
    // Verificamos si el tipo de arma existe en el mapa y asignamos las texturas
    auto it = gunTextures.find(typeGun);
    if (it != gunTextures.end()) {
        texture_path_equipped = it->second.first;
        texture_path_not_equipped = it->second.second;
    }
}