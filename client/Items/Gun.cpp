#include "Gun.h"

#include <SDL_render.h>

#define IMAGE_COWBOY_GUN DATA_PATH "/weapons/CowboyPistol.png"
#define IMAGE_COWBOY_GUN_EQUIPPED DATA_PATH "/weapons/CowboyPistolEquipped.png"
#define IMAGE_AK47_GUN DATA_PATH "/weapons/ak47.png"
#define IMAGE_AK47_GUN_EQUIPPED DATA_PATH "/weapons/ak47Equipped.png"
#define IMAGE_PISTOLA_DUELOS_GUN DATA_PATH "/weapons/duelingPistol.png"
#define IMAGE_PISTOLA_DUELOS_GUN_EQUIPPED DATA_PATH "/weapons/duelingPistolEquipped.png"
#define IMAGE_MAGNUM_GUN DATA_PATH "/weapons/magnum.png"
#define IMAGE_MAGNUM_GUN_EQUIPPED DATA_PATH "/weapons/magnumEquipped.png"
#define IMAGE_ESCOPETA_GUN DATA_PATH "/weapons/shotgun.png"
#define IMAGE_ESCOPETA_GUN_EQUIPPED DATA_PATH "/weapons/shotgunEquipped.png"
#define IMAGE_SNIPER_GUN DATA_PATH "/weapons/sniper.png"
#define IMAGE_SNIPER_GUN_EQUIPPED DATA_PATH "/weapons/sniperEquipped.png"
#define IMAGE_GRANADA_GUN DATA_PATH "/weapons/grenade.png"
#define IMAGE_GRANADA_GUN_EQUIPPED DATA_PATH "/weapons/grenadeEquipped.png"
#define IMAGE_BANANA_GUN DATA_PATH "/weapons/banana.png"
#define IMAGE_BANANA_GUN_EQUIPPED DATA_PATH "/weapons/bananaEquipped.png"
#define IMAGE_PEW_PEW_LASER_GUN DATA_PATH "/weapons/PewpewLaser.png"
#define IMAGE_PEW_PEW_LASER_GUN_EQUIPPED DATA_PATH "/weapons/PewpewLaserEquipped.png"
#define IMAGE_LASER_RIFLE_GUN DATA_PATH "/weapons/laserRifle.png"
#define IMAGE_LASER_RIFLE_GUN_EQUIPPED DATA_PATH "/weapons/laserRifleEquipped.png"


Gun::Gun(Graficos& graficos, float pos_x, float pos_y, uint8_t typeOfGun):
        graficos(graficos),
        typeOfGun(typeOfGun),
        is_equiped(false),
        pos_x(pos_x),
        pos_y(pos_y),
        lookingUp(false) {}

void Gun::draw(bool isFliped, SDL2pp::Renderer& renderer) {
    if (typeOfGun == NOGUN) {
        return;
    }
    const char* texture_path_equipped;
    const char* texture_path_not_equipped;
    int with = WIDTH_GUN;
    int height = HEIGHT_GUN;
    actualizarTextura(texture_path_equipped, texture_path_not_equipped, with, height);

    Texture texture_equipped(graficos.LoadTexture(texture_path_equipped));
    Texture texture_not_equipped(graficos.LoadTexture(texture_path_not_equipped));

    if (is_equiped) {
        // si esta flippeado dibujo a todas por igual
        if (isFliped) {
            if (lookingUp) {
                renderer.Copy(
                        texture_equipped, SDL2pp::NullOpt,
                        Rect(pos_x - DUCK_WIDTH / 2.5, pos_y - DUCK_HEIGHT / 2.5, with, height),
                        90.0, SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
            } else
                renderer.Copy(texture_equipped, SDL2pp::NullOpt,
                              Rect(pos_x - DUCK_WIDTH / 2.5, pos_y, with, height), 0.0,
                              SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
        } else if (lookingUp) {
            renderer.Copy(texture_equipped, SDL2pp::NullOpt,
                          Rect(pos_x + 3, pos_y - DUCK_HEIGHT / 2.5, with, height), 90.0,
                          SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
        }
        // si no esta flippeado dibujo a las granadas y bananas distinto
        else if (typeOfGun == GRANADA_GUN || typeOfGun == BANANA_GUN)
            renderer.Copy(texture_equipped, SDL2pp::NullOpt, Rect(pos_x + 5, pos_y, with, height));
        else
            renderer.Copy(texture_equipped, SDL2pp::NullOpt, Rect(pos_x, pos_y, with, height));

    } else {
        if (isFliped)  // no tendría que usarlo por que estaría en el piso pero por las dudas
            renderer.Copy(texture_not_equipped, SDL2pp::NullOpt, Rect(pos_x, pos_y, with, height),
                          0.0, SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
        else
            renderer.Copy(texture_not_equipped, SDL2pp::NullOpt, Rect(pos_x, pos_y, with, height));
    }
}

bool Gun::isEquipped() { return typeOfGun != NOGUN && is_equiped; }

void Gun::setEquip(bool equip) { is_equiped = equip; }

void Gun::setGun(uint8_t gun, bool look_up) {
    typeOfGun = gun;
    if (gun == NOGUN)
        is_equiped = false;
    else
        is_equiped = true;
    lookingUp = look_up;
}

void Gun::update(float new_x, float new_y) {
    pos_x = new_x;
    pos_y = new_y;
}

float Gun::getPosX() { return pos_x; }

float Gun::getPosY() { return pos_y; }

void Gun::actualizarTextura(const char*& texture_equipped, const char*& texture_not_equipped,
                            int& width, int& height) {
    switch (typeOfGun) {
        case NOGUN:
            break;
        case COWBOY_GUN:
            texture_equipped = IMAGE_COWBOY_GUN_EQUIPPED;
            texture_not_equipped = IMAGE_COWBOY_GUN;
            break;
        case AK47_GUN:
            texture_equipped = IMAGE_AK47_GUN_EQUIPPED;
            texture_not_equipped = IMAGE_AK47_GUN;
            break;
        case PISTOLA_DUELOS_GUN:
            texture_equipped = IMAGE_PISTOLA_DUELOS_GUN_EQUIPPED;
            texture_not_equipped = IMAGE_PISTOLA_DUELOS_GUN;
            break;
        case MAGNUM_GUN:
            texture_equipped = IMAGE_MAGNUM_GUN_EQUIPPED;
            texture_not_equipped = IMAGE_MAGNUM_GUN;
            break;
        case ESCOPETA_GUN:
            texture_equipped = IMAGE_ESCOPETA_GUN_EQUIPPED;
            texture_not_equipped = IMAGE_ESCOPETA_GUN;
            break;
        case SNIPER_GUN:
            texture_equipped = IMAGE_SNIPER_GUN_EQUIPPED;
            texture_not_equipped = IMAGE_SNIPER_GUN;
            break;
        case GRANADA_GUN:
            texture_equipped = IMAGE_GRANADA_GUN_EQUIPPED;
            texture_not_equipped = IMAGE_GRANADA_GUN;
            width = WIDTH_GRENADE_BANANA;
            height = HEIGHT_GRENADE_BANANA;
            break;
        case BANANA_GUN:
            texture_equipped = IMAGE_BANANA_GUN_EQUIPPED;
            texture_not_equipped = IMAGE_BANANA_GUN;
            width = WIDTH_GRENADE_BANANA;
            height = HEIGHT_GRENADE_BANANA;
            break;
        case PEW_PEW_LASER_GUN:
            texture_equipped = IMAGE_PEW_PEW_LASER_GUN_EQUIPPED;
            texture_not_equipped = IMAGE_PEW_PEW_LASER_GUN;
            break;
        case LASER_RIFLE_GUN:
            texture_equipped = IMAGE_LASER_RIFLE_GUN_EQUIPPED;
            texture_not_equipped = IMAGE_LASER_RIFLE_GUN;
            break;
        default:
            break;
    }
}
