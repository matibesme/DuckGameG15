#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2pp/SDL2pp.hh>
#include <list>
#include "Graficos.h"
#include "../common/dto_definitions.h"

class Background{
private:
    SDL2pp::Texture background;
    SDL2pp::Texture platform;
    SDL2pp::Texture platform_base;
    SDL2pp::Texture backgroundTexture;
    void draw2(Graficos& graficos, std::list<DTOPlataform> lista_plataformas, uint8_t background_id);

public:
    Background(Graficos& graficos);
    void drawBackGruond(SDL2pp::Renderer& renderer);
    void drawPlataforms(SDL2pp::Renderer& renderer);
    SDL2pp::Rect rangeOfCollision(SDL2pp::Renderer& renderer);
    Background(Graficos &graficos, std::list<DTOPlataform> lista_plataformas, uint8_t background_id);
    void renderBackground(SDL2pp::Renderer& renderer);
};

#endif