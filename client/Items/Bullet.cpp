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
#define IMAGE_BANANA_BULLET DATA_PATH "/banana.png"

Bullet::Bullet(uint8_t id, float initial_pos_x, float initial_pos_y, Graficos& graficos, uint8_t orientacion, uint8_t type) :
          graficos(graficos), idBullet(id),
          pos_x(initial_pos_x), pos_y(initial_pos_y),
          orientationOfBullet(orientacion), typeOfBullet(type) {}

void Bullet::draw(SDL2pp::Renderer& renderer) {
    //CUIDADO = llegan como int por parametro, pero se guardan como float

    const char* texture_path;
    actualizarTipo(texture_path);
    Texture texture (graficos.LoadTexture(texture_path));

    Rect area;
    int height, width;        // Dimensiones de la bala
    //tipo de area dependiendo de la orientacion y si es bala o granada o banana
    if((typeOfBullet == C_GRANADA_BULLET || typeOfBullet == C_BANANA_BULLET) && orientationOfBullet == BULLET_UP){
        height = HEIGHT_GRENADE_BANANA;
        width = WIDTH_GRENADE_BANANA;
        area = Rect(pos_x, pos_y, width, height);
    }else if((typeOfBullet == C_GRANADA_BULLET || typeOfBullet == C_BANANA_BULLET)
                                               && orientationOfBullet == BULLET_RIGTH){
        height = HEIGHT_GRENADE_BANANA;
        width = WIDTH_GRENADE_BANANA;
        area = Rect(pos_x + DUCK_WIDTH / 2, pos_y + DUCK_HEIGHT, width, height);
    } else if ((typeOfBullet == C_GRANADA_BULLET || typeOfBullet == C_BANANA_BULLET)
                                                 && orientationOfBullet == BULLET_LEFT){
        height = HEIGHT_GRENADE_BANANA;
        width = WIDTH_GRENADE_BANANA;
        area = Rect(pos_x, pos_y + DUCK_HEIGHT, width, height);
    } else if (orientationOfBullet == BULLET_UP){
        height = HEIGHT_BULLET;
        width = WIDTH_BULLET;
        area = Rect(pos_x, pos_y, height, width);
    } else if(orientationOfBullet == BULLET_RIGTH){
        height = HEIGHT_BULLET;
        width = WIDTH_BULLET;
        area = Rect(pos_x + DUCK_WIDTH, pos_y + DUCK_HEIGHT / 2, width, height);
    } else if(orientationOfBullet == BULLET_LEFT){
        height = HEIGHT_BULLET;
        width = WIDTH_BULLET;
        area = Rect(pos_x, pos_y + DUCK_HEIGHT/2, width, height);
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

void Bullet::update(const float new_pos_x,const float new_pos_y, [[maybe_unused]]const uint8_t type, const uint8_t orientacion) {
    pos_x = new_pos_x;
    pos_y = new_pos_y;
    orientationOfBullet = orientacion;
    //actualizarTipo(typeOfBullet);
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
