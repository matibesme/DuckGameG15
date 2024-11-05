#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include "Graficos.h"
#include "Background.h"
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
    Background& background;
    static SDL2pp::Rect calcularRectanguloDeZoom(std::list<ClientDuck>& ducks);

public:
    explicit GameRenderer(Graficos& graficos, Background& background);

    void dibujar(Renderer& renderer, std::list<ClientDuck>& ducks, std::list<Bullet>& bullets,
                 std::list<Gun>& guns, std::list<Armor>& armors, std::list<Helmet>& helmets);

    void actualizarElementos(const GameState &command, std::list<ClientDuck>& ducks, std::list<Bullet>& bullets,
                             std::list<Gun>& guns, std::list<Armor>& armors, std::list<Helmet>& helmets);

};

#endif // GAMERENDERER_H
