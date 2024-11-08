#include <SDL_render.h>
#include "Bullet.h"

#define IMAGE_AMMO_1 DATA_PATH "/bullets/ammo.png"
#define IMAGE_AMMO_2 DATA_PATH "/bullets/ammo2.png"
#define IMAGE_AMMO_3 DATA_PATH "/bullets/ammo3.png"
#define IMAGE_AMMO_4 DATA_PATH "/bullets/ammo4.png"
#define IMAGE_AMMO_5 DATA_PATH "/bullets/ammo5.png"
#define IMAGE_LASER_AMMO DATA_PATH "/bullets/laserAmmo.png"
#define IMAGE_LASER_AMMO2 DATA_PATH "/bullets/laserAmmo2.png"
#define IMAGE_GRANADA_BULLET DATA_PATH "/bullets/thrownGrenade.png"
#define IMAGE_GRANADA_EXPLOTION DATA_PATH "/bullets/explode.png"
#define IMAGE_BANANA_BULLET DATA_PATH "/bullets/banana.png"
#define IMAGE_BANANA_THROWN DATA_PATH "/bullets/thrownBanana.png"
#define SPRITE_WIDTH_BULLET (384/6)
#define SPRITE_HEIGHT_BULLET 64

Bullet::Bullet(uint8_t id, float initial_pos_x, float initial_pos_y, Graficos& graficos, uint8_t orientacion, uint8_t type) :
        graficos(graficos), idBullet(id),
        pos_x(initial_pos_x), pos_y(initial_pos_y),
        orientationOfBullet(orientacion), typeOfBullet(type),
        explotionSpriteX(-1){}

void Bullet::draw(SDL2pp::Renderer& renderer) {

    const char* texture_path;
    actualizarTipo(texture_path);
    Texture texture (graficos.LoadTexture(texture_path));

    Rect area;
    //tipo de area dependiendo de la orientacion y si es bala o granada o banana
    if((typeOfBullet == GRANADA_BULLET || typeOfBullet == BANANA_BULLET)
                                        && orientationOfBullet == BULLET_UP){

        area = Rect(pos_x, pos_y, WIDTH_GRENADE_BANANA, HEIGHT_GRENADE_BANANA);

    } else if((typeOfBullet == GRANADA_BULLET || typeOfBullet == BANANA_BULLET)
                                               && orientationOfBullet == BULLET_RIGHT){

        area = Rect(pos_x + DUCK_WIDTH / 2, pos_y, WIDTH_GRENADE_BANANA, HEIGHT_GRENADE_BANANA);

    } else if ((typeOfBullet == GRANADA_BULLET || typeOfBullet == BANANA_BULLET)
                                                 && orientationOfBullet == BULLET_LEFT){

        area = Rect(pos_x, pos_y, WIDTH_GRENADE_BANANA, HEIGHT_GRENADE_BANANA);

    } else if (orientationOfBullet == BULLET_UP){
        area = Rect(pos_x, pos_y, HEIGHT_BULLET, WIDTH_BULLET);

    } else if(typeOfBullet == GRENADE_EXPLOSION){
        explotionSpriteX = (explotionSpriteX + 1);
        // destRect es el rectángulo donde se dibujará la textura
        SDL2pp::Rect destRect((int)pos_x , (int)pos_y + DUCK_HEIGHT / 5, WIDTH_GRENADE_EXPLOTION, HEIGHT_GRENADE_EXPLOTION);
        // srcRect es el rectángulo que se tomará de la textura
        SDL2pp::Rect srcRect(explotionSpriteX * SPRITE_WIDTH_BULLET, 0, SPRITE_WIDTH_BULLET, SPRITE_HEIGHT_BULLET);
        renderer.Copy(texture, srcRect, destRect);
        return;
    }
    else if(orientationOfBullet == BULLET_RIGHT){
        area = Rect(pos_x + DUCK_WIDTH, pos_y + DUCK_HEIGHT / 2, WIDTH_BULLET, HEIGHT_BULLET);

    } else if(orientationOfBullet == BULLET_LEFT){
        area = Rect(pos_x, pos_y + DUCK_HEIGHT/2, WIDTH_BULLET, HEIGHT_BULLET);

    } else {
        return;
    }

    // Si la orientacion es tanto gira o para arriba o para los costados
    if(orientationOfBullet == BULLET_LEFT)
        renderer.Copy(texture, SDL2pp::NullOpt, area, 0.0, SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
    else if (orientationOfBullet == BULLET_RIGHT)
        renderer.Copy(texture, SDL2pp::NullOpt, area);
    else if (orientationOfBullet == BULLET_UP)
        renderer.Copy(texture, SDL2pp::NullOpt, area, 90.0, SDL2pp::NullOpt, SDL_FLIP_NONE);
}

void Bullet::update(const float new_pos_x,const float new_pos_y, const uint8_t type, const uint8_t orientacion) {
    pos_x = new_pos_x;
    pos_y = new_pos_y;
    orientationOfBullet = orientacion;
    typeOfBullet = type;
}

void Bullet::actualizarTipo(const char*& texture) {
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

uint8_t Bullet::getId() const {
    return idBullet;
}
