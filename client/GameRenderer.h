#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include <list>

#include "Items/Box.h"
#include "Items/Bullet.h"
#include "Items/ClientDuck.h"
#include "Items/Gun.h"
#include "Items/Platform.h"
#include "Items/armor.h"
#include "Items/helmet.h"

#include "Graficos.h"
#include "dto_definitions.h"

class GameRenderer {
private:
    Graficos& graficos;
    std::list<ClientDuck> ducks;
    std::list<Bullet> bullets;
    std::list<Gun> guns;
    std::list<Armor> armors;
    std::list<Helmet> helmets;
    std::list<Platform> platforms;
    std::list<Box> boxes;
    static SDL2pp::Rect calcularRectanguloDeZoom(std::list<ClientDuck>& ducks);
    void drawBackground(const uint8_t background_id);

public:
    explicit GameRenderer(Graficos& graficos, std::list<DTOPlatform>& platforms,
                          std::list<DTOBoxes>& boxes);

    void dibujar(Renderer& renderer, GameState& command);


    void actualizarElementos(const GameState& command);
};

#endif  // GAMERENDERER_H
