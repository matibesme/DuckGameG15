#include "Background.h"

Background::Background(Graficos& graficos) : background(graficos.LoadTexture(DATA_PATH "/fondo_prueba.jpg")), platform(graficos.LoadTexture(DATA_PATH "/plataforma_prueba.png")){

}

void Background::draw(SDL2pp::Renderer& renderer){
    renderer.Copy(background);

    SDL2pp::Rect destRect = rangeOfCollision(renderer);

    renderer.Copy(platform, SDL2pp::NullOpt, destRect);
}

SDL2pp::Rect Background::rangeOfCollision(SDL2pp::Renderer& renderer){
    int platformHeight = platform.GetHeight();
    int platformWidth = platform.GetWidth();

    int posX = (renderer.GetOutputWidth() - platformWidth) / 2;
    int posY = (renderer.GetOutputHeight() - platformHeight) / 1.5;

    SDL2pp::Rect destRect(posX, posY, platformWidth, platformHeight);

    return destRect;
}