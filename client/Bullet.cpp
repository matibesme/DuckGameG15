#include <SDL_render.h>
#include "Bullet.h"

// Constructor para inicializar la bala con la textura y dimensiones predeterminadas
Bullet::Bullet(float initial_pos_x, float initial_pos_y, Graficos& graficos)
        : texture(graficos.LoadTexture(DATA_PATH "/CowboyBullet.png")),
          pos_x(initial_pos_x), pos_y(initial_pos_y),
          height(HEIGHT_BULLET), width(WIDTH_BULLET),
          orientationOfBullet(false), typeOfBullet(0) {}

void Bullet::draw(SDL2pp::Renderer& renderer) {
    //CUIDADO = llegan como int por parametro, pero se guardan como float
    SDL2pp::Rect area_gun(pos_x, pos_y, width, height);

    // Si la orientacion es tanto gira o para arriba o para los costados
    if(orientationOfBullet)
        //map con typeOfBullet a texture
        renderer.Copy(texture, SDL2pp::NullOpt, area_gun, 0.0, SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
    else
        renderer.Copy(texture, SDL2pp::NullOpt, area_gun);

}

void Bullet::update(float new_pos_x, float new_pos_y, uint8_t type, uint8_t orientacion) {
    this->pos_x = new_pos_x;
    this->pos_y = new_pos_y;
    orientationOfBullet = orientacion;
    typeOfBullet = type;
}
