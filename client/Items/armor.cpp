#include <SDL_render.h>
#include "armor.h"

#define IMAGE_ARMOR DATA_PATH "/pechera.png"

Armor::Armor(Graficos& graficos, float pos_x, float pos_y)
        : graficos(graficos), is_equipped(false), pos_x(pos_x), pos_y(pos_y) {}

void Armor::draw(bool isFliped, SDL2pp::Renderer& renderer) {
    Texture texture(graficos.LoadTexture(IMAGE_ARMOR));

    //if (is_equipped) {
        if (isFliped)
            renderer.Copy(texture, SDL2pp::NullOpt, Rect(pos_x - DUCK_WIDTH / 9, pos_y, WIDTH_ARMOR, HEIGHT_ARMOR), 0.0, SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
        else
            renderer.Copy(texture, SDL2pp::NullOpt, Rect(pos_x - DUCK_WIDTH / 9 , pos_y, WIDTH_ARMOR, HEIGHT_ARMOR));
    //}else{
    //    renderer.Copy(texture, SDL2pp::NullOpt, Rect(pos_x, pos_y + 20, WIDTH_ARMOR, HEIGHT_ARMOR));
    //}
}

bool Armor::isEquipped() {
    return is_equipped;
}

void Armor::equip() {
    is_equipped = true;
}

void Armor::unequip() {
    is_equipped = false;
}

void Armor::update(float new_x, float new_y) {
    pos_x = new_x;
    pos_y = new_y;
}

float Armor::getPosX() {
    return pos_x;
}

float Armor::getPosY() {
    return pos_y;
}
