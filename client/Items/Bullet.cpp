#include <SDL_render.h>
#include "Bullet.h"

#define IMAGE_CHAIN_BULLET DATA_PATH "/chainBullet.png"

Bullet::Bullet(uint8_t id, float initial_pos_x, float initial_pos_y, Graficos& graficos, uint8_t orientacion, uint8_t type) :
          graficos(graficos), idBullet(id),
          pos_x(initial_pos_x), pos_y(initial_pos_y),
          height(HEIGHT_BULLET), width(WIDTH_BULLET),
          orientationOfBullet(orientacion), typeOfBullet(type) {}

void Bullet::draw(SDL2pp::Renderer& renderer) {
    //CUIDADO = llegan como int por parametro, pero se guardan como float

    const char* texture_path;
    actualizarTipo(texture_path);

    Texture texture (graficos.LoadTexture(texture_path));

    // Si la orientacion es tanto gira o para arriba o para los costados
    if(orientationOfBullet == BULLET_LEFT)
        //map con typeOfBullet a texture
        renderer.Copy(texture, SDL2pp::NullOpt, Rect(pos_x, pos_y + DUCK_HEIGHT/2, width, height), 0.0, SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
    else if (orientationOfBullet == BULLET_RIGTH)
        renderer.Copy(texture, SDL2pp::NullOpt, Rect(pos_x + DUCK_WIDTH, pos_y + DUCK_HEIGHT/2, width, height));
    else if (orientationOfBullet == BULLET_UP)
        renderer.Copy(texture, SDL2pp::NullOpt, Rect(pos_x, pos_y, height, width), 90.0, SDL2pp::NullOpt, SDL_FLIP_NONE);
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
        default:
            break;
    }

}

uint8_t Bullet::getId() const {
    return idBullet;
}
