#include <SDL_render.h>
#include "Bullet.h"

#define IMAGE_CHAIN_BULLET DATA_PATH "/chainBullet.png"
#define IMAGE_AMMO_1 DATA_PATH "/ammo.png"
#define IMAGE_AMMO_2 DATA_PATH "/ammo2.png"
#define IMAGE_AMMO_3 DATA_PATH "/ammo3.png"
#define IMAGE_AMMO_4 DATA_PATH "/ammo4.png"
#define IMAGE_AMMO_5 DATA_PATH "/ammo5.png"
#define IMAGE_LASER_AMMO DATA_PATH "/laserAmmo.png"
#define IMAGE_LASER_AMMO2 DATA_PATH "/laserAmmo2.png"
#define IMAGE_GRANADA_BULLET DATA_PATH "/grenade.png"
#define IMAGE_GRANADA_EXPLOTION DATA_PATH "/explode.png"
#define IMAGE_BANANA_BULLET DATA_PATH "/banana.png"
#define SPRITE_WIDTH (384/6)
#define SPRITE_HEIGHT 64

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
    if((typeOfBullet == C_GRANADA_BULLET || typeOfBullet == C_BANANA_BULLET) && orientationOfBullet == BULLET_UP){
        area = Rect(pos_x, pos_y, WIDTH_GRENADE_BANANA, HEIGHT_GRENADE_BANANA);
    } else if((typeOfBullet == C_GRANADA_BULLET || typeOfBullet == C_BANANA_BULLET)
                                               && orientationOfBullet == BULLET_RIGTH){
        area = Rect(pos_x + DUCK_WIDTH / 2, pos_y + DUCK_HEIGHT, WIDTH_GRENADE_BANANA, HEIGHT_GRENADE_BANANA);
    } else if ((typeOfBullet == C_GRANADA_BULLET || typeOfBullet == C_BANANA_BULLET)
                                                 && orientationOfBullet == BULLET_LEFT){
        area = Rect(pos_x, pos_y + DUCK_HEIGHT, WIDTH_GRENADE_BANANA, HEIGHT_GRENADE_BANANA);
    } else if (orientationOfBullet == BULLET_UP){
        area = Rect(pos_x, pos_y, HEIGHT_BULLET, WIDTH_BULLET);
    } else if(typeOfBullet == C_GRANADA_EXPLOTION){
        explotionSpriteX = (explotionSpriteX + 1);
        // destRect es el rectángulo donde se dibujará la textura
        SDL2pp::Rect destRect((int)pos_x , (int)pos_y + DUCK_HEIGHT / 5, WIDTH_GRANADE_EXPLOTION, HEIGHT_GRANADE_EXPLOTION);
        // srcRect es el rectángulo que se tomará de la textura
        SDL2pp::Rect srcRect(explotionSpriteX * SPRITE_WIDTH, 0, SPRITE_WIDTH, SPRITE_HEIGHT);
        renderer.Copy(texture, srcRect, destRect);
        return;
    }
    else if(orientationOfBullet == BULLET_RIGTH){
        area = Rect(pos_x + DUCK_WIDTH, pos_y + DUCK_HEIGHT / 2, WIDTH_BULLET, HEIGHT_BULLET);
    } else if(orientationOfBullet == BULLET_LEFT){
        area = Rect(pos_x, pos_y + DUCK_HEIGHT/2, WIDTH_BULLET, HEIGHT_BULLET);
    } else {
        return;
    }

    // Si la orientacion es tanto gira o para arriba o para los costados
    if(orientationOfBullet == BULLET_LEFT)
        renderer.Copy(texture, SDL2pp::NullOpt, area, 0.0, SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
    else if (orientationOfBullet == BULLET_RIGTH)
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
        case C_COWBOY_BULLET:
            texture = IMAGE_CHAIN_BULLET;
            break;
        case C_AK47_BULLET:
            texture = IMAGE_AMMO_1;
            break;
        case C_PISTOLA_DUELOS_BULLET:
            texture = IMAGE_AMMO_2;
            break;
        case C_MAGNUM_BULLET:
            texture = IMAGE_AMMO_3;
            break;
        case C_ESCOPETA_BULLET:
            texture = IMAGE_AMMO_4;
            break;
        case C_SNIPER_BULLET:
            texture = IMAGE_AMMO_5;
            break;
        case C_PEW_PEW_LASER_BULLET:
            texture = IMAGE_LASER_AMMO;
            break;
        case C_LASER_RIFLE_BULLET:
            texture = IMAGE_LASER_AMMO2;
            break;
        case C_GRANADA_BULLET:
            texture = IMAGE_GRANADA_BULLET;
            break;
        case C_GRANADA_EXPLOTION:
            texture = IMAGE_GRANADA_EXPLOTION;
            break;
        case C_BANANA_BULLET:
            texture = IMAGE_BANANA_BULLET;
            break;
        default:
            break;
    }
}

uint8_t Bullet::getId() const {
    return idBullet;
}
