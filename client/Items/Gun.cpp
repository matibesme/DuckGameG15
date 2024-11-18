#include "Gun.h"

#include <SDL_render.h>

#define IMAGE_COWBOY_GUN DATA_PATH "/weapons/cowboyPistol.png"
#define IMAGE_COWBOY_GUN_EQUIPPED DATA_PATH "/weapons/CowboyPistolEquipped.png"
#define IMAGE_AK47_GUN DATA_PATH "/weapons/ak47.png"
#define IMAGE_AK47_GUN_EQUIPPED DATA_PATH "/weapons/ak47Equipped.png"
#define IMAGE_PISTOLA_DUELOS_GUN DATA_PATH "/weapons/duelingPistol.png"
#define IMAGE_PISTOLA_DUELOS_GUN_EQUIPPED                                      \
  DATA_PATH "/weapons/duelingPistolEquipped.png"
#define IMAGE_MAGNUM_GUN DATA_PATH "/weapons/magnum.png"
#define IMAGE_MAGNUM_GUN_EQUIPPED DATA_PATH "/weapons/magnumEquipped.png"
#define IMAGE_ESCOPETA_GUN DATA_PATH "/weapons/shotgun.png"
#define IMAGE_ESCOPETA_GUN_EQUIPPED DATA_PATH "/weapons/shotgunEquipped.png"
#define IMAGE_SNIPER_GUN DATA_PATH "/weapons/sniper.png"
#define IMAGE_SNIPER_GUN_EQUIPPED DATA_PATH "/weapons/sniperEquipped.png"
#define IMAGE_GRANADA_GUN DATA_PATH "/weapons/grenade.png"
#define IMAGE_GRANADA_GUN_EQUIPPED DATA_PATH "/weapons/grenadeEquipped.png"
#define IMAGE_BANANA_GUN DATA_PATH "/weapons/bananaSpawn.png"
#define IMAGE_BANANA_GUN_EQUIPPED DATA_PATH "/weapons/bananaEquipped.png"
#define IMAGE_PEW_PEW_LASER_GUN DATA_PATH "/weapons/PewpewLaser.png"
#define IMAGE_PEW_PEW_LASER_GUN_EQUIPPED                                       \
  DATA_PATH "/weapons/PewpewLaserEquipped.png"
#define IMAGE_LASER_RIFLE_GUN DATA_PATH "/weapons/laserRifle.png"
#define IMAGE_LASER_RIFLE_GUN_EQUIPPED                                         \
  DATA_PATH "/weapons/laserRifleEquipped.png"

Gun::Gun(Graficos &graficos, float pos_x, float pos_y, uint8_t typeOfGun)
    : graficos(graficos), posX(pos_x), posY(pos_y), typeGun(typeOfGun) {
  cargarTextura();
}

void Gun::cargarTextura() {
  const char *texture_path_equipped = nullptr;
  const char *texture_path_not_equipped = nullptr;
  int width = 0, height = 0;

  actualizarTextura(texture_path_equipped, texture_path_not_equipped, width,
                    height);
  if (typeGun == NOGUN)
    return;
  texture_equipped = std::make_unique<SDL2pp::Texture>(
      graficos.LoadTexture(texture_path_equipped));

  texture_not_equipped = std::make_unique<SDL2pp::Texture>(
      graficos.LoadTexture(texture_path_not_equipped));
}

void Gun::drawOnDuck(float newX, float newY, bool isFliped, uint8_t gun,
                     bool lookingUp, SDL2pp::Renderer &renderer) {
  if (gun != typeGun) {
    typeGun = gun;
    cargarTextura();
  }
  if (!texture_equipped || typeGun == NOGUN) {
    return;
  }
  posX = newX;
  posY = newY;
  auto &active_texture = *texture_equipped;

  // si esta flippeado dibujo a todas por igual
  if (isFliped) {
    if (lookingUp) {
      renderer.Copy(active_texture, SDL2pp::NullOpt,
                    Rect(posX - DUCK_WIDTH / 2.5, posY - DUCK_HEIGHT / 2.5,
                         WIDTH_GUN, HEIGHT_GUN),
                    90.0, SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
    } else
      renderer.Copy(active_texture, SDL2pp::NullOpt,
                    Rect(posX - DUCK_WIDTH / 2.5, posY, WIDTH_GUN, HEIGHT_GUN),
                    0.0, SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
  } else if (lookingUp) {
    renderer.Copy(
        active_texture, SDL2pp::NullOpt,
        Rect(posX + 3, posY - DUCK_HEIGHT / 2.5, WIDTH_GUN, HEIGHT_GUN), 90.0,
        SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
  }
  // si no esta flippeado dibujo a las granadas y bananas distinto
  else if (typeGun == GRANADA_GUN || typeGun == BANANA_GUN)
    renderer.Copy(active_texture, SDL2pp::NullOpt,
                  Rect(posX + 5, posY, WIDTH_GUN, HEIGHT_GUN));
  else
    renderer.Copy(active_texture, SDL2pp::NullOpt,
                  Rect(posX, posY, WIDTH_GUN, HEIGHT_GUN));
}

void Gun::drawOnSpawn(SDL2pp::Renderer &renderer) {
  if (!texture_not_equipped || typeGun == NOGUN) {
    return;
  }
  auto &active_texture = *texture_not_equipped;

  if (typeGun == BANANA_GUN) {
    // destRect es el rectángulo donde se dibujará el pato
    SDL2pp::Rect destRect(posX, posY, WIDTH_GUN, HEIGHT_GUN);
    // srcRect es el rectángulo que se tomará de la textura
    SDL2pp::Rect srcRect(0, 32, 16, 16);

    renderer.Copy(active_texture, srcRect, destRect);
  } else
    renderer.Copy(active_texture, SDL2pp::NullOpt,
                  Rect(posX, posY, WIDTH_GUN, HEIGHT_GUN));
}

float Gun::getPosX() { return posX; }

float Gun::getPosY() { return posY; }

void Gun::actualizarTextura(const char *&texture_path_equipped,
                            const char *&texture_path_not_equipped, int &width,
                            int &height) {
  switch (typeGun) {
  case NOGUN:
    break;
  case COWBOY_GUN:
    texture_path_equipped = IMAGE_COWBOY_GUN_EQUIPPED;
    texture_path_not_equipped = IMAGE_COWBOY_GUN;
    break;
  case AK47_GUN:
    texture_path_equipped = IMAGE_AK47_GUN_EQUIPPED;
    texture_path_not_equipped = IMAGE_AK47_GUN;
    break;
  case PISTOLA_DUELOS_GUN:
    texture_path_equipped = IMAGE_PISTOLA_DUELOS_GUN_EQUIPPED;
    texture_path_not_equipped = IMAGE_PISTOLA_DUELOS_GUN;
    break;
  case MAGNUM_GUN:
    texture_path_equipped = IMAGE_MAGNUM_GUN_EQUIPPED;
    texture_path_not_equipped = IMAGE_MAGNUM_GUN;
    break;
  case ESCOPETA_GUN:
    texture_path_equipped = IMAGE_ESCOPETA_GUN_EQUIPPED;
    texture_path_not_equipped = IMAGE_ESCOPETA_GUN;
    break;
  case SNIPER_GUN:
    texture_path_equipped = IMAGE_SNIPER_GUN_EQUIPPED;
    texture_path_not_equipped = IMAGE_SNIPER_GUN;
    break;
  case GRANADA_GUN:
    texture_path_equipped = IMAGE_GRANADA_GUN_EQUIPPED;
    texture_path_not_equipped = IMAGE_GRANADA_GUN;
    width = WIDTH_GRENADE_BANANA;
    height = HEIGHT_GRENADE_BANANA;
    break;
  case BANANA_GUN:
    texture_path_equipped = IMAGE_BANANA_GUN_EQUIPPED;
    texture_path_not_equipped = IMAGE_BANANA_GUN;
    width = WIDTH_GRENADE_BANANA;
    height = HEIGHT_GRENADE_BANANA;
    break;
  case PEW_PEW_LASER_GUN:
    texture_path_equipped = IMAGE_PEW_PEW_LASER_GUN_EQUIPPED;
    texture_path_not_equipped = IMAGE_PEW_PEW_LASER_GUN;
    break;
  case LASER_RIFLE_GUN:
    texture_path_equipped = IMAGE_LASER_RIFLE_GUN_EQUIPPED;
    texture_path_not_equipped = IMAGE_LASER_RIFLE_GUN;
    break;
  default:
    break;
  }
}
