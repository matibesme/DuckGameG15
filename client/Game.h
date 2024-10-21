#ifndef GAME_H
#define GAME_H

#include "Duck.h"
#include "Graficos.h"
#include "Background.h"
#include "protocolo_cliente.h"

class Game {
public:
    Game(ProtocoloCliente& protocol);
    void run();

private:
    Graficos graficos;
    Duck duck;
    Background background;
    unsigned int prevTicks;
    SDL2pp::Texture duckTexture;
    ProtocoloCliente& protocol;
};

#endif // GAME_H
