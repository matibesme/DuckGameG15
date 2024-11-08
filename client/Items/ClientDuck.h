#ifndef PLAYER_H
#define PLAYER_H

#include "SDL2pp/SDL2pp.hh"
#include "../common/common_constant.h"
#include "Gun.h"
#include "Graficos.h"
#include <memory>
#include "armor.h"
#include "helmet.h"

using namespace SDL2pp;

class ClientDuck {
public:
    ClientDuck(uint8_t id, float initial_pos_x, float initial_pos_y, uint8_t typeOfGun, uint8_t typeOfMove,
               Graficos& graficos);
    void update(float y_pos, float x_pos, uint8_t typeOfMove, uint8_t gunEquipped);
    void draw(Renderer& renderer);
    uint8_t getId() const;
    int getPosX();
    int getPosY();

private:
    uint8_t idDuck;
    float positionX;
    float positionY;
    Graficos& graficos;
    int numSprite;
    Gun gun;
    bool isFlipped;
    uint8_t typeOfGun;
    float pixelDuckSpriteX;
    float pixelDuckSpriteY;
    std::unique_ptr<SDL2pp::Texture> coloredTexture;

    Armor armor;
    Helmet helmet;
    void applyColor(Renderer& renderer);
};

#endif // PLAYER_H
