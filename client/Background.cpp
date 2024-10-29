#include "Background.h"
#define IMAGE_PAISAJE DATA_PATH "/fondo_prueba.jpg"
#define IMAGE_PLATAFORMA_CHICA DATA_PATH "/plataforma_prueba.png"
#define IMAGE_PLATAFORMA_GRANDE DATA_PATH "/plataforma_larga_prueba.png"

Background::Background(Graficos& graficos) : background(graficos.LoadTexture(IMAGE_PAISAJE)),
            platform(graficos.LoadTexture(IMAGE_PLATAFORMA_CHICA)),
            platform_base(graficos.LoadTexture(IMAGE_PLATAFORMA_GRANDE)){}

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

Background::Background(Graficos &graficos, std::list<DTOPlataform> lista_plataformas, uint8_t background_id)
            :background(nullptr),
            platform(nullptr),
            platform_base(nullptr){
    draw2(graficos, lista_plataformas, background_id);
}

void Background::draw2(Graficos& graficos, std::list<DTOPlataform> lista_plataformas, uint8_t background_id) {
    //ten en cuenta que el background_id es para saber que fondo cargar, de imagen luego el tipo de plataforma
    //es para saber que plataforma cargar
    if (background_id == 1) {
        background = graficos.LoadTexture(IMAGE_PAISAJE);
    } else {
        background = graficos.LoadTexture(IMAGE_PAISAJE);
    }

    if (lista_plataformas.empty()) {
        return;
    }

    for (auto & plataforma : lista_plataformas) {
        if (plataforma.typeOfPlataform == 1) {
            platform = graficos.LoadTexture(IMAGE_PLATAFORMA_GRANDE);
        } else {
            platform = graficos.LoadTexture(IMAGE_PLATAFORMA_GRANDE);
        }

        int platformHeight = platform.GetHeight();
        int platformWidth = platform.GetWidth();

        int posX = plataforma.x_pos;
        int posY = plataforma.y_pos;

        SDL2pp::Rect destRect(posX, posY, platformWidth, platformHeight);

        graficos.GetRenderer().Copy(platform, SDL2pp::NullOpt, destRect);
    }
}
