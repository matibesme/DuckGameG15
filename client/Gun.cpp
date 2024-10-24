#include <SDL_render.h>
#include "Gun.h"

/*Gun::Gun(float initial_pos_x, float initial_pos_y, int height, int width, SDL2pp::Texture& texture_equipped, SDL2pp::Texture& texture_not_equipped) 
            : texture_not_equipped(texture_not_equipped), texture_equipped(texture_equipped), height(height), width(width){
    pos_x = initial_pos_x;
    pos_y = initial_pos_y;
    is_equipped = false;
}*/

Gun::Gun(Graficos& graficos) : texture_equipped(graficos.LoadTexture(DATA_PATH "/CowboyPistolEquipped.png")), 
                                texture_not_equipped(graficos.LoadTexture(DATA_PATH "/CowboyPistol.png")),
                                height(HEIGHT_GUN), width(WIDTH_GUN) , typeOfGun(C_NOGUN), is_equiped(false),
                                pos_x(0), pos_y(0){}

void Gun::draw(bool isFliped, SDL2pp::Renderer& renderer){
    if(typeOfGun == C_NOGUN){
        return;
    }

    //CUIDADO = llegan como int por parametro, pero se guardan como float
    SDL2pp::Rect area_gun(pos_x, pos_y, width, height);

    if(is_equiped){
        //map con typeOfGun a textura
        if (isFliped)
        renderer.Copy(texture_equipped, SDL2pp::NullOpt, area_gun, 0.0, SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
        else
        renderer.Copy(texture_equipped, SDL2pp::NullOpt, area_gun);
    } else{
        if (isFliped)
        renderer.Copy(texture_not_equipped, SDL2pp::NullOpt, area_gun, 0.0, SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
        else
        renderer.Copy(texture_not_equipped, SDL2pp::NullOpt, area_gun);
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
