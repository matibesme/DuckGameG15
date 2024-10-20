#ifndef GAME_H
#define GAME_H

#include "Duck.h"
#include "Graficos.h"
#include "Background.h"

class Game {
public:
    Game();
    void run();

private:
    Graficos graficos;
    Duck duck;
    Background background;
    unsigned int prevTicks;
    SDL2pp::Texture duckTexture;
};

#endif // GAME_H
