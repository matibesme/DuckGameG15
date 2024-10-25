#include <SDL_render.h>
#include "Bullet.h"

#define IMAGE_CHAIN_BULLET DATA_PATH "/chainBullet.png"

Bullet::Bullet(float initial_pos_x, float initial_pos_y, Graficos& graficos)
        : graficos(graficos), texture(graficos.LoadTexture(IMAGE_CHAIN_BULLET)),
          pos_x(initial_pos_x), pos_y(initial_pos_y),
          height(HEIGHT_BULLET), width(WIDTH_BULLET),
          orientationOfBullet(false) {}

void Bullet::draw(SDL2pp::Renderer& renderer) {
    //CUIDADO = llegan como int por parametro, pero se guardan como float
    SDL2pp::Rect area_gun(pos_x, pos_y, width, height);

    // Si la orientacion es tanto gira o para arriba o para los costados
    if(orientationOfBullet == BULLET_LEFT)
        //map con typeOfBullet a texture
        renderer.Copy(texture, SDL2pp::NullOpt, area_gun, 0.0, SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
    else if (orientationOfBullet == BULLET_RIGTH)
        renderer.Copy(texture, SDL2pp::NullOpt, area_gun);
    else if (orientationOfBullet == BULLET_UP)
        renderer.Copy(texture, SDL2pp::NullOpt, area_gun, 90.0, SDL2pp::NullOpt, SDL_FLIP_NONE);
    else
        renderer.Copy(texture, SDL2pp::NullOpt, area_gun);
}

void Bullet::update(const float new_pos_x,const float new_pos_y, [[maybe_unused]]const uint8_t typeOfBullet, const uint8_t orientacion) {
    pos_x = new_pos_x;
    pos_y = new_pos_y;
    orientationOfBullet = orientacion;
    //actualizarTipo(typeOfBullet);
}

void Bullet::actualizarTipo(const uint8_t type) {
    switch (type) {
        case C_COWBOY_BULLET:
            texture = graficos.LoadTexture(IMAGE_CHAIN_BULLET);
            break;
        default:
            break;
    }

}
