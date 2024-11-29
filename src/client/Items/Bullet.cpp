#include "Bullet.h"

#include "constantTextures.h"
#include <SDL_render.h>

#define SOUND_COWBOY DATA_PATH "/sound/pistol.wav"
#define SOUND_AK47 DATA_PATH "/sound/netGunFire.wav"
#define SOUND_PISTOLA DATA_PATH "/sound/pistolFire.wav"
#define SOUND_MAGNUM DATA_PATH "/sound/magShot.wav"
#define SOUND_ESCOPETA DATA_PATH "/sound/shotgunFire.wav"
#define SOUND_SNIPER DATA_PATH "/sound/sniper.wav"
#define SOUND_LASER DATA_PATH "/sound/laserRifle.wav"
#define SOUND_GRANADA DATA_PATH "/sound/grenadeFire.wav"
#define SPRITE_WIDTH_BULLET (384 / 6)
#define SPRITE_HEIGHT_BULLET 64
#define PRIMERA_ITERACION 0
#define CENTER_EXPLODE_GRANADE_X 10
#define CENTER_EXPLODE_GRANADE_Y 20
Bullet::Bullet(uint8_t id, float initial_pos_x, float initial_pos_y,
               Graficos &graficos, uint8_t orientacion, uint8_t type)
    : graficos(graficos), idBullet(id), pos_x(initial_pos_x),
      pos_y(initial_pos_y), orientationOfBullet(orientacion),
      typeOfBullet(type), explosionSpriteX(-1), iteracion(PRIMERA_ITERACION) {
  reproducirSonido();
}

void Bullet::draw(SDL2pp::Renderer &renderer) {
  // haz una condicion se cumpla solo al principio una vez para reproducir el
  // sonido
  if (iteracion == PRIMERA_ITERACION)
    reproducirSonido();

  const char *texture_path;
  actualizarTipo(texture_path);
  Texture &texture = graficos.getTexture(texture_path);

  SDL2pp::Rect area;
  // tipo de area dependiendo de la orientacion y si es bala o granada o banana
  if (typeOfBullet == GRANADA_BULLET || typeOfBullet == BANANA_BULLET) {
    area =
        SDL2pp::Rect(pos_x, pos_y, WIDTH_GRENADE_BANANA, HEIGHT_GRENADE_BANANA);
  } else if (typeOfBullet == GRENADE_EXPLOSION) {
    explosionSpriteX = (explosionSpriteX + 1);
    if (explosionSpriteX == 0) {
      reproducirSonido();
    }
    // destRect es el rectángulo donde se dibujará la textura
    SDL2pp::Rect destRect((int)pos_x-CENTER_EXPLODE_GRANADE_X, (int)pos_y-CENTER_EXPLODE_GRANADE_Y, WIDTH_GRENADE_EXPLOTION,
                          HEIGHT_GRENADE_EXPLOTION);
    // srcRect es el rectángulo que se tomará de la textura
    SDL2pp::Rect srcRect(explosionSpriteX * SPRITE_WIDTH_BULLET, 0,
                         SPRITE_WIDTH_BULLET, SPRITE_HEIGHT_BULLET);
    renderer.Copy(texture, srcRect, destRect);
    return;
  } else {
    area = SDL2pp::Rect(pos_x, pos_y, WIDTH_BULLET, HEIGHT_BULLET);
  }
  // Si la orientacion es tanto para arriba o para los costados
  if (orientationOfBullet == BULLET_LEFT)
    renderer.Copy(texture, SDL2pp::NullOpt, area, 0.0, SDL2pp::NullOpt,
                  SDL_FLIP_HORIZONTAL);
  else if (orientationOfBullet == BULLET_RIGHT)
    renderer.Copy(texture, SDL2pp::NullOpt, area);
  else if (orientationOfBullet == BULLET_UP)
    renderer.Copy(texture, SDL2pp::NullOpt, area, 90.0, SDL2pp::NullOpt,
                  SDL_FLIP_NONE);
}

void Bullet::update(const float new_pos_x, const float new_pos_y,
                    const uint8_t type, const uint8_t orientacion) {
  pos_x = new_pos_x;
  pos_y = new_pos_y;
  orientationOfBullet = orientacion;
  typeOfBullet = type;
}

void Bullet::actualizarTipo(const char *&texture) {
  switch (typeOfBullet) {
  case COWBOY_BULLET:
    texture = IMAGE_AMMO_1;
    break;
  case AK47_BULLET:
    texture = IMAGE_AMMO_1;
    break;
  case PISTOLA_DUELOS_BULLET:
    texture = IMAGE_AMMO_2;
    break;
  case MAGNUM_BULLET:
    texture = IMAGE_AMMO_3;
    break;
  case ESCOPETA_BULLET:
    texture = IMAGE_AMMO_4;
    break;
  case SNIPER_BULLET:
    texture = IMAGE_AMMO_5;
    break;
  case PEW_PEW_LASER_BULLET:
    texture = IMAGE_LASER_AMMO;
    break;
  case LASER_RIFLE_BULLET:
    texture = IMAGE_LASER_AMMO2;
    break;
  case GRANADA_BULLET:
    texture = IMAGE_GRANADA_BULLET;
    break;
  case GRENADE_EXPLOSION:
    texture = IMAGE_GRANADA_EXPLOTION;
    break;
  case BANANA_BULLET:
    texture = IMAGE_BANANA_BULLET;
    break;
  default:
    break;
  }
}

void Bullet::reproducirSonido() {
  iteracion++;
  sound.inicializar();
  switch (typeOfBullet) {
  case COWBOY_BULLET:
    sound.reproducirEfecto(SOUND_COWBOY);
    break;
  case AK47_BULLET:
    sound.reproducirEfecto(SOUND_AK47);
    break;
  case PISTOLA_DUELOS_BULLET:
    sound.reproducirEfecto(SOUND_PISTOLA);
    break;
  case MAGNUM_BULLET:
    sound.reproducirEfecto(SOUND_MAGNUM);
    break;
  case ESCOPETA_BULLET:
    sound.reproducirEfecto(SOUND_ESCOPETA);
    break;
  case SNIPER_BULLET:
    sound.reproducirEfecto(SOUND_SNIPER);
    break;
  case PEW_PEW_LASER_BULLET:
    sound.reproducirEfecto(SOUND_LASER);
    break;
  case LASER_RIFLE_BULLET:
    sound.reproducirEfecto(SOUND_LASER);
    break;
  case GRENADE_EXPLOSION:
    sound.reproducirEfecto(SOUND_GRANADA);
    break;
  default:
    break;
  }
}

uint8_t Bullet::getId() const { return idBullet; }
