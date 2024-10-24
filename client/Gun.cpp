#include "Gun.h"

/*Gun::Gun(float initial_pos_x, float initial_pos_y, int height, int width, SDL2pp::Texture& texture_equipped, SDL2pp::Texture& texture_not_equipped) 
            : texture_not_equipped(texture_not_equipped), texture_equipped(texture_equipped), height(height), width(width){
    pos_x = initial_pos_x;
    pos_y = initial_pos_y;
    is_equipped = false;
}*/

Gun::Gun(Graficos& graficos) : texture_equipped(graficos.LoadTexture(DATA_PATH "/CowboyPistolEquipped.png")), 
                                texture_not_equipped(graficos.LoadTexture(DATA_PATH "/CowboyPistol.png")), height(13), width(25){
    pos_x = 0.0;
    pos_y = 0.0;
    is_equipped = false;
}

void Gun::draw(SDL2pp::Renderer& renderer){
    /*
    Esto también se podría implementar con el sprite del ala (duckArms.png) para que se pueda animar el ala aparte.
    */
    SDL2pp::Rect area_gun(pos_x, pos_y, width, height);

    if(is_equipped){
        renderer.Copy(texture_equipped, SDL2pp::NullOpt, area_gun);
    }else{
        renderer.Copy(texture_not_equipped, SDL2pp::NullOpt, area_gun);
    }
    
}

void Gun::update_pos(float pos_x, float pos_y){
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

bool Gun::get_is_equipped(){
    return is_equipped;
}

void Gun::set_is_equipped(bool is_equipped){
    this->is_equipped = is_equipped;
}