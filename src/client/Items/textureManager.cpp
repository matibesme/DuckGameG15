#include "textureManager.h"
#include "constantTextures.h"

TextureManager::TextureManager(Renderer &renderer) : renderer(renderer) {
    // Se cargarán todas las texturas con sus rutas asociadas
    textures = {
            {ARMOR_EQUIPPED, DATA_PATH "/armour/pechera.png"},
            {HELMET_EQUIPPED, DATA_PATH "/armour/casco.png"},
            {TYPE_BOX, DATA_PATH "/objects/itemBox.png"},
            {GRENADE_EXPLOSION, DATA_PATH "/bullets/explode.png"},
            {COWBOY_BULLET, DATA_PATH "/bullets/ammo.png"},
            {AK47_BULLET, DATA_PATH "/bullets/ammo.png"},
            {PISTOLA_DUELOS_BULLET, DATA_PATH "/bullets/ammo2.png"},
            {MAGNUM_BULLET, DATA_PATH "/bullets/ammo3.png"},
            {ESCOPETA_BULLET, DATA_PATH "/bullets/ammo4.png"},
            {SNIPER_BULLET, DATA_PATH "/bullets/ammo5.png"},
            {PEW_PEW_LASER_BULLET, DATA_PATH "/bullets/laserAmmo.png"},
            {LASER_RIFLE_BULLET, DATA_PATH "/bullets/laserAmmo2.png"},
            {GRANADA_BULLET, DATA_PATH "/bullets/thrownGrenade.png"},
            {BANANA_BULLET, DATA_PATH "/bullets/banana.png"},
            {COWBOY_GUN, DATA_PATH "/weapons/cowboyPistol.png"},
            {COWBOY_GUN_EQUIPPED, DATA_PATH "/weapons/CowboyPistolEquipped.png"},
            {AK47_GUN, DATA_PATH "/weapons/ak47.png"},
            {AK47_GUN_EQUIPPED, DATA_PATH "/weapons/ak47Equipped.png"},
            {PISTOLA_DUELOS_GUN, DATA_PATH "/weapons/duelingPistol.png"},
            {PISTOLA_DUELOS_GUN_EQUIPPED, DATA_PATH "/weapons/duelingPistolEquipped.png"},
            {MAGNUM_GUN, DATA_PATH "/weapons/magnum.png"},
            {MAGNUM_GUN_EQUIPPED, DATA_PATH "/weapons/magnumEquipped.png"},
            {ESCOPETA_GUN, DATA_PATH "/weapons/shotgun.png"},
            {ESCOPETA_GUN_EQUIPPED, DATA_PATH "/weapons/shotgunEquipped.png"},
            {SNIPER_GUN, DATA_PATH "/weapons/sniper.png"},
            {SNIPER_GUN_EQUIPPED, DATA_PATH "/weapons/sniperEquipped.png"},
            {GRANADA_GUN, DATA_PATH "/weapons/grenade.png"},
            {GRANADA_GUN_EQUIPPED, DATA_PATH "/weapons/grenadeEquipped.png"},
            {BANANA_GUN, DATA_PATH "/weapons/bananaSpawn.png"},
            {BANANA_GUN_EQUIPPED, DATA_PATH "/weapons/bananaEquipped.png"},
            {PEW_PEW_LASER_GUN, DATA_PATH "/weapons/PewpewLaser.png"},
            {PEW_PEW_LASER_GUN_EQUIPPED, DATA_PATH "/weapons/PewpewLaserEquipped.png"},
            {LASER_RIFLE_GUN, DATA_PATH "/weapons/laserRifle.png"},
            {LASER_RIFLE_GUN_EQUIPPED, DATA_PATH "/weapons/laserRifleEquipped.png"},
            {TYPE_PLATFORM_DONUT, DATA_PATH "/platforms/Donut.png"}
    };
    loadTextures();
}

void TextureManager::loadTextures() {
    for (auto &texture : textures) {
        textures[texture.first] = renderer.LoadTexture(texture.second);
    }
}

SDL2pp::Texture &TextureManager::getTexture(uint8_t id) {
    return textures[id];
}
