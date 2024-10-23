#include "Background.h"

Background::Background(Graficos& graficos) : background(graficos.LoadTexture(DATA_PATH "/fondo_prueba.jpg")), platform(graficos.LoadTexture(DATA_PATH "/plataforma_prueba.png")), platform_base(graficos.LoadTexture(DATA_PATH "/plataforma_larga_prueba.png")){

}

void Background::draw(SDL2pp::Renderer& renderer){
    renderer.Copy(background);

    SDL2pp::Rect destRect = rangeOfCollision(renderer);

    int platformHeight = platform_base.GetHeight();
    int platformWidth = platform_base.GetWidth();

    int posX = (renderer.GetOutputWidth() - platformWidth) / 2 - 8;
    int posY = (renderer.GetOutputHeight() - platformHeight) + 50;


    SDL2pp::Rect destRectBase(posX, posY, platformWidth, platformHeight);

    renderer.Copy(platform, SDL2pp::NullOpt, destRect);
    renderer.Copy(platform_base, SDL2pp::NullOpt, destRectBase);
}

SDL2pp::Rect Background::rangeOfCollision(SDL2pp::Renderer& renderer){
    int platformHeight = platform.GetHeight();
    int platformWidth = platform.GetWidth();

    int posX = (renderer.GetOutputWidth() - platformWidth) / 2;
    int posY = (renderer.GetOutputHeight() - platformHeight) / 1.5;

    SDL2pp::Rect destRect(posX, posY, platformWidth, platformHeight);

    return destRect;
}