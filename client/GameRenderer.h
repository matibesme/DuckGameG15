#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include "Graficos.h"
#include "Background.h"
#include "Items/ClientDuck.h"
#include "Items/Bullet.h"
#include "Items/Gun.h"
#include "dto_definitions.h"
#include <list>

class GameRenderer {
private:
    Graficos& graficos;
    Background background;

public:
    explicit GameRenderer(Graficos& graficos);

    void dibujar(Renderer& renderer, std::list<ClientDuck>& ducks,
                 std::list<Bullet>& bullets, std::list<Gun>& guns);

    void actualizarElementos(const CommandGameShow &command, std::list<ClientDuck> &ducks,
                             std::list<Bullet> &bullets, std::list<Gun> &guns);

};

#endif // GAMERENDERER_H
