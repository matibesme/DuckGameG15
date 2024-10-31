#include <SDL_render.h>
#include "helmet.h"

#define IMAGE_HELMET DATA_PATH "/casco.png"

Helmet::Helmet(Graficos& graficos, float pos_x, float pos_y)
        : graficos(graficos), is_equipped(false), pos_x(pos_x), pos_y(pos_y) {}

void Helmet::draw(bool isFliped, SDL2pp::Renderer& renderer) {
    Texture texture(graficos.LoadTexture(IMAGE_HELMET));

    //if (is_equipped) {
        if (isFliped)
            renderer.Copy(texture, SDL2pp::NullOpt, Rect(pos_x - DUCK_WIDTH * 0.1, pos_y - DUCK_HEIGHT / 2.5, WIDTH_HELMET, HEIGHT_HELMET), 0.0, SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
        else
            renderer.Copy(texture, SDL2pp::NullOpt, Rect(pos_x - DUCK_WIDTH / 9, pos_y - DUCK_HEIGHT / 2.5, WIDTH_HELMET, HEIGHT_HELMET));
    //}else{
    //    renderer.Copy(texture, SDL2pp::NullOpt, Rect(pos_x, pos_y + 20, WIDTH_HELMET, HEIGHT_HELMET));
}

bool Helmet::isEquipped() {
    return is_equipped;
}

void Helmet::equip() {
    is_equipped = true;
}

void Helmet::unequip() {
    is_equipped = false;
}

void Helmet::update(float new_x, float new_y) {
    pos_x = new_x;
    pos_y = new_y;
}

float Helmet::getPosX() {
    return pos_x;
}

float Helmet::getPosY() {
    return pos_y;
}