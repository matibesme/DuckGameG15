#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include "Graficos.h"
#include "Items/Platform.h"
#include "Items/ClientDuck.h"
#include "Items/Bullet.h"
#include "Items/Gun.h"
#include "Items/helmet.h"
#include "Items/armor.h"
#include "dto_definitions.h"
#include <list>

class GameRenderer {
private:
    Graficos& graficos;
    std::list<ClientDuck> ducks;
    std::list<Bullet> bullets;
    std::list<Gun> guns;
    std::list<Armor> armors;
    std::list<Helmet> helmets;
    std::list<Platform> platforms;
    static SDL2pp::Rect calcularRectanguloDeZoom(std::list<ClientDuck>& ducks);
    void drawBackground(uint8_t background_id);

public:
    explicit GameRenderer(Graficos& graficos);

    void dibujar(Renderer& renderer, GameState& command);


    void actualizarElementos(const GameState &command);

};

#endif // GAMERENDERER_H
