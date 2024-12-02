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
    SDL2pp::Rect destRect((int)pos_x - CENTER_EXPLODE_GRANADE_X,
                          (int)pos_y - CENTER_EXPLODE_GRANADE_Y,
                          WIDTH_GRENADE_EXPLOTION, HEIGHT_GRENADE_EXPLOTION);
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
  static const std::map<uint8_t, const char *> texture_map = {
      {COWBOY_BULLET, IMAGE_AMMO_1},
      {AK47_BULLET, IMAGE_AMMO_1},
      {PISTOLA_DUELOS_BULLET, IMAGE_AMMO_2},
      {MAGNUM_BULLET, IMAGE_AMMO_3},
      {ESCOPETA_BULLET, IMAGE_AMMO_4},
      {SNIPER_BULLET, IMAGE_AMMO_5},
      {PEW_PEW_LASER_BULLET, IMAGE_LASER_AMMO},
      {LASER_RIFLE_BULLET, IMAGE_LASER_AMMO2},
      {GRANADA_BULLET, IMAGE_GRANADA_BULLET},
      {GRENADE_EXPLOSION, IMAGE_GRANADA_EXPLOTION},
      {BANANA_BULLET, IMAGE_BANANA_BULLET}};
  texture = texture_map.at(typeOfBullet);
}

void Bullet::reproducirSonido() {
  if (typeOfBullet == BANANA_BULLET || typeOfBullet == GRANADA_BULLET)
    return;

  iteracion++;
  Sound::inicializar();

  static const std::map<uint8_t, const char *> sound_map = {
      {COWBOY_BULLET, SOUND_COWBOY},          {AK47_BULLET, SOUND_AK47},
      {PISTOLA_DUELOS_BULLET, SOUND_PISTOLA}, {MAGNUM_BULLET, SOUND_MAGNUM},
      {ESCOPETA_BULLET, SOUND_ESCOPETA},      {SNIPER_BULLET, SOUND_SNIPER},
      {PEW_PEW_LASER_BULLET, SOUND_LASER},    {LASER_RIFLE_BULLET, SOUND_LASER},
      {GRENADE_EXPLOSION, SOUND_GRANADA}};
  sound.reproducirEfecto(sound_map.at(typeOfBullet));
}

uint8_t Bullet::getId() const { return idBullet; }
