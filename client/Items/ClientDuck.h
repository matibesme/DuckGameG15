#ifndef PLAYER_H
#define PLAYER_H

#include "SDL2pp/SDL2pp.hh"
#include "../common/common_constant.h"
#include "Gun.h"
#include "Graficos.h"
#include <memory>
#include "armor.h"
#include "helmet.h"
#include <map>

using namespace SDL2pp;

class ClientDuck {
public:
    ClientDuck(uint8_t id, float initial_pos_x, float initial_pos_y, uint8_t typeOfGun, uint8_t typeOfMove,
                std::string color, Graficos& graficos);
    void update(float y_pos, float x_pos, uint8_t typeOfMove, uint8_t gunEquipped, uint8_t armor,
                uint8_t helmet, bool lookingUp);
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
    bool armorEquipped;
    bool helmetEquipped;
    bool isOnGround;
    void applyColor(Renderer& renderer, const std::string& color);
    //defineme un mapa de colores para los patos
    std::map<std::string, SDL_Color> colorMap = {
                  {"red", {255, 0, 0, 255}},
                  {"blue", {0, 0, 255, 255}},
                  {"green", {0, 255, 0, 255}},
                  {"yellow", {255, 255, 0, 255}},
                  {"pink", {255, 105, 180, 255}},
                  {"purple", {128, 0, 128, 255}},
                  {"orange", {255, 165, 0, 255}},
                  {"brown", {165, 42, 42, 255}},
                  {"black", {0, 0, 0, 255}},
                  {"white", {255, 255, 255, 255}}
    };
};

#endif // PLAYER_H
