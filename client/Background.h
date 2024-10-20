#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2pp/SDL2pp.hh>
#include "Graficos.h"

class Background{
private:
    SDL2pp::Texture background;
public:
    Background(Graficos& graficos);
    void draw(SDL2pp::Renderer& renderer);
};

#endif