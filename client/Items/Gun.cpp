#include <SDL_render.h>
#include "Gun.h"

#define IMAGE_COWBOY_GUN DATA_PATH "/CowboyPistol.png"
#define IMAGE_COWBOY_GUN_EQUIPPED DATA_PATH "/CowboyPistolEquipped.png"

Gun::Gun(Graficos& graficos, float pos_x, float pos_y, uint8_t typeOfGun) :
        graficos(graficos), typeOfGun(typeOfGun), is_equiped(false),
        pos_x(pos_x), pos_y(pos_y) {}

void Gun::draw(bool isFliped, SDL2pp::Renderer& renderer){
    if(typeOfGun == C_NOGUN){
        return;
    }
    const char* texture_path_equipped;
    const char* texture_path_not_equipped;
    actualizarTextura(texture_path_equipped, texture_path_not_equipped);

    Texture texture_equipped (graficos.LoadTexture(texture_path_equipped));
    Texture texture_not_equipped (graficos.LoadTexture(texture_path_not_equipped));

    if(is_equiped){
        //map con typeOfGun a textura
        if (isFliped)
            renderer.Copy(texture_not_equipped, SDL2pp::NullOpt, Rect(pos_x - DUCK_WIDTH/2, pos_y, WIDTH_GUN, HEIGHT_GUN), 0.0, SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
        else
            renderer.Copy(texture_equipped, SDL2pp::NullOpt, Rect(pos_x, pos_y, WIDTH_GUN, HEIGHT_GUN));
    } else{
        if (isFliped)
            renderer.Copy(texture_not_equipped, SDL2pp::NullOpt, Rect(pos_x - DUCK_WIDTH/2, pos_y, WIDTH_GUN, HEIGHT_GUN), 0.0, SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
        else
            renderer.Copy(texture_not_equipped, SDL2pp::NullOpt, Rect(pos_x, pos_y, WIDTH_GUN, HEIGHT_GUN));
    }
}

bool Gun::isEquipped(){
    return typeOfGun != C_NOGUN && is_equiped;
}

void Gun::setEquip(bool equip){
    is_equiped = equip;
}

void Gun::setGun(uint8_t gun){
    typeOfGun = gun;
    if(gun == C_NOGUN)
        is_equiped = false;
    else
        is_equiped = true;
}

void Gun::actualizarTextura(const char*& texture_equipped, const char*& texture_not_equipped) {
    switch (typeOfGun) {
        case C_NOGUN:
            break;
        case C_COWBOY_GUN:
            texture_equipped = IMAGE_COWBOY_GUN_EQUIPPED;
            texture_not_equipped = IMAGE_COWBOY_GUN;
            break;
    }
}

void Gun::update(float new_x, float new_y) {
    pos_x = new_x;
    pos_y = new_y;
}
