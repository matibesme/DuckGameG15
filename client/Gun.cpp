#include <SDL_render.h>
#include "Gun.h"

#define IMAGE_COWBOY_GUN DATA_PATH "/CowboyPistol.png"
#define IMAGE_COWBOY_GUN_EQUIPPED DATA_PATH "/CowboyPistolEquipped.png"

Gun::Gun(Graficos& graficos) :  graficos(graficos), typeOfGun(C_NOGUN), is_equiped(false),
                                pos_x(0), pos_y(0), texture_equipped(graficos.LoadTexture(IMAGE_COWBOY_GUN_EQUIPPED)),
                                texture_not_equipped(graficos.LoadTexture(IMAGE_COWBOY_GUN)){}

void Gun::draw(bool isFliped, SDL2pp::Renderer& renderer){
    if(typeOfGun == C_NOGUN){
        return;
    }

    actualizarTextura();

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

void Gun::update_pos(float posX, float posY){
    this->pos_x = posX;
    this->pos_y = posY;
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

void Gun::actualizarTextura() {
    switch (typeOfGun) {
        case C_NOGUN:
            break;
        case C_COWBOY_GUN:
            texture_equipped = graficos.LoadTexture(IMAGE_COWBOY_GUN_EQUIPPED);
            texture_not_equipped = graficos.LoadTexture(IMAGE_COWBOY_GUN);
            break;
    }
}
