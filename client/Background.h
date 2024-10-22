#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2pp/SDL2pp.hh>
#include "Graficos.h"

class Background{
private:
    SDL2pp::Texture background;
    SDL2pp::Texture platform;
    SDL2pp::Texture platform_base;
public:
    Background(Graficos& graficos);
    void draw(SDL2pp::Renderer& renderer);
    SDL2pp::Rect rangeOfCollision(SDL2pp::Renderer& renderer);
};

#endif