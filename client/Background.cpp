#include "Background.h"

Background::Background(Graficos& graficos) : background(graficos.LoadTexture(DATA_PATH "/fondo_prueba.jpg")){

}

void Background::draw(SDL2pp::Renderer& renderer){
    renderer.Copy(background);
}