#include <SDL_render.h>
#include "Gun.h"

#define IMAGE_COWBOY_GUN DATA_PATH "/CowboyPistol.png"
#define IMAGE_COWBOY_GUN_EQUIPPED DATA_PATH "/CowboyPistolEquipped.png"
#define IMAGE_AK47_GUN DATA_PATH "/ak47.png"
#define IMAGE_AK47_GUN_EQUIPPED DATA_PATH "/ak47Equipped.png"
#define IMAGE_PISTOLA_DUELOS_GUN DATA_PATH "/duelingPistol.png"
#define IMAGE_PISTOLA_DUELOS_GUN_EQUIPPED DATA_PATH "/duelingPistolEquipped.png"
#define IMAGE_MAGNUM_GUN DATA_PATH "/magnum.png"
#define IMAGE_MAGNUM_GUN_EQUIPPED DATA_PATH "/magnumEquipped.png"
#define IMAGE_ESCOPETA_GUN DATA_PATH "/shotgun.png"
#define IMAGE_ESCOPETA_GUN_EQUIPPED DATA_PATH "/shotgunEquipped.png"
#define IMAGE_SNIPER_GUN DATA_PATH "/sniper.png"
#define IMAGE_SNIPER_GUN_EQUIPPED DATA_PATH "/sniperEquipped.png"
#define IMAGE_GRANADA_GUN DATA_PATH "/grenade.png"
#define IMAGE_GRANADA_GUN_EQUIPPED DATA_PATH "/grenadeEquipped.png"
#define IMAGE_BANANA_GUN DATA_PATH "/banana.png"
#define IMAGE_BANANA_GUN_EQUIPPED DATA_PATH "/bananaEquipped.png"
#define IMAGE_PEW_PEW_LASER_GUN DATA_PATH "/PewpewLaser.png"
#define IMAGE_PEW_PEW_LASER_GUN_EQUIPPED DATA_PATH "/PewpewLaserEquipped.png"
#define IMAGE_LASER_RIFLE_GUN DATA_PATH "/laserRifle.png"
#define IMAGE_LASER_RIFLE_GUN_EQUIPPED DATA_PATH "/laserRifleEquipped.png"

Gun::Gun(Graficos& graficos, float pos_x, float pos_y, uint8_t typeOfGun) :
        graficos(graficos), typeOfGun(typeOfGun), is_equiped(false),
        pos_x(pos_x), pos_y(pos_y) {}

void Gun::draw(bool isFliped, SDL2pp::Renderer& renderer){
    if(typeOfGun == C_NOGUN){
        return;
    }
    const char* texture_path_equipped;
    const char* texture_path_not_equipped;
    int with = WIDTH_GUN;
    int height = HEIGHT_GUN;
    actualizarTextura(texture_path_equipped, texture_path_not_equipped, with, height);

    Texture texture_equipped (graficos.LoadTexture(texture_path_equipped));
    Texture texture_not_equipped (graficos.LoadTexture(texture_path_not_equipped));

    if(is_equiped){
        //map con typeOfGun a textura
        if (isFliped) {
            if( typeOfGun == C_GRANADA_GUN || typeOfGun == C_BANANA_GUN)
                renderer.Copy(texture_not_equipped, SDL2pp::NullOpt, Rect(pos_x - DUCK_WIDTH_CLIENT / 5, pos_y, with, height), 0.0,
                              SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
            else
            renderer.Copy(texture_not_equipped, SDL2pp::NullOpt, Rect(pos_x - DUCK_WIDTH_CLIENT / 2, pos_y, with, height), 0.0,
                          SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
        }
        else
            renderer.Copy(texture_equipped, SDL2pp::NullOpt, Rect(pos_x, pos_y, with, height));
    } else{
        if (isFliped)
            renderer.Copy(texture_not_equipped, SDL2pp::NullOpt, Rect(pos_x, pos_y, with, height), 0.0, SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
        else
            renderer.Copy(texture_not_equipped, SDL2pp::NullOpt, Rect(pos_x, pos_y, with, height));
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

void Gun::update(float new_x, float new_y) {
    pos_x = new_x;
    pos_y = new_y;
}

float Gun::getPosX() {
    return pos_x;
}

float Gun::getPosY() {
    return pos_y;
}

void Gun::actualizarTextura(const char*& texture_equipped, const char*& texture_not_equipped, int &width, int &height) {
    switch (typeOfGun) {
        case C_NOGUN:
            break;
        case C_COWBOY_GUN:
            texture_equipped = IMAGE_COWBOY_GUN_EQUIPPED;
            texture_not_equipped = IMAGE_COWBOY_GUN;
            break;
        case C_AK47_GUN:
            texture_equipped = IMAGE_AK47_GUN_EQUIPPED;
            texture_not_equipped = IMAGE_AK47_GUN;
            break;
        case C_PISTOLA_DUELOS_GUN:
            texture_equipped = IMAGE_PISTOLA_DUELOS_GUN_EQUIPPED;
            texture_not_equipped = IMAGE_PISTOLA_DUELOS_GUN;
            break;
        case C_MAGNUM_GUN:
            texture_equipped = IMAGE_MAGNUM_GUN_EQUIPPED;
            texture_not_equipped = IMAGE_MAGNUM_GUN;
            break;
        case C_ESCOPETA_GUN:
            texture_equipped = IMAGE_ESCOPETA_GUN_EQUIPPED;
            texture_not_equipped = IMAGE_ESCOPETA_GUN;
            break;
        case C_SNIPER_GUN:
            texture_equipped = IMAGE_SNIPER_GUN_EQUIPPED;
            texture_not_equipped = IMAGE_SNIPER_GUN;
            break;
        case C_GRANADA_GUN:
            texture_equipped = IMAGE_GRANADA_GUN_EQUIPPED;
            texture_not_equipped = IMAGE_GRANADA_GUN;
            width = WIDTH_GRENADE_BANANA;
            height = HEIGHT_GRENADE_BANANA;
            break;
        case C_BANANA_GUN:
            texture_equipped = IMAGE_BANANA_GUN_EQUIPPED;
            texture_not_equipped = IMAGE_BANANA_GUN;
            width = WIDTH_GRENADE_BANANA;
            height = HEIGHT_GRENADE_BANANA;
            break;
        case C_PEW_PEW_LASER_GUN:
            texture_equipped = IMAGE_PEW_PEW_LASER_GUN_EQUIPPED;
            texture_not_equipped = IMAGE_PEW_PEW_LASER_GUN;
            break;
        case C_LASER_RIFLE_GUN:
            texture_equipped = IMAGE_LASER_RIFLE_GUN_EQUIPPED;
            texture_not_equipped = IMAGE_LASER_RIFLE_GUN;
            break;
        default:
            break;
    }
}
