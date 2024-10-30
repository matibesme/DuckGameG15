#include <SDL_render.h>
#include "Background.h"
#define IMAGE_PAISAJE DATA_PATH "/fondo_prueba.jpg"
#define IMAGE_PLATAFORMA_CHICA DATA_PATH "/plataforma_prueba.png"
#define IMAGE_PLATAFORMA_GRANDE DATA_PATH "/plataforma_larga_prueba.png"

Background::Background(Graficos& graficos) : background(graficos.LoadTexture(IMAGE_PAISAJE)),
            platform(graficos.LoadTexture(IMAGE_PLATAFORMA_CHICA)),
            platform_base(graficos.LoadTexture(IMAGE_PLATAFORMA_GRANDE)),
            backgroundTexture(Texture(graficos.GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 640, 480)){}

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

Background::Background(Graficos& graficos_, std::list<DTOPlataform> lista_plataformas, uint8_t background_id)
        : background(graficos_.LoadTexture(IMAGE_PAISAJE)),
          platform(graficos_.LoadTexture(IMAGE_PLATAFORMA_CHICA)),
          platform_base(graficos_.LoadTexture(IMAGE_PLATAFORMA_GRANDE)),
          backgroundTexture(Texture(graficos_.GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 640, 480))
{
    draw2(graficos_, lista_plataformas, background_id);
}

void Background::draw2(Graficos& graficos, std::list<DTOPlataform> lista_plataformas, uint8_t background_id) {
    Renderer& renderer = graficos.GetRenderer();

    // Establecer la textura como el target del renderer
    SDL_SetRenderTarget(renderer.Get(), backgroundTexture.Get());

    // Cargar y dibujar el fondo
    if (background_id == 1) {
        background = graficos.LoadTexture(IMAGE_PAISAJE);
    } else {
        background = graficos.LoadTexture(IMAGE_PAISAJE);
    }

    // Copiar el fondo en la textura
    renderer.Copy(background, SDL2pp::NullOpt, SDL2pp::NullOpt);

    // Dibujar las plataformas
    if (!lista_plataformas.empty()) {
        for (auto& plataforma : lista_plataformas) {
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
            renderer.Copy(platform, SDL2pp::NullOpt, destRect);
        }
    }

    // Resetear el target del renderer al predeterminado
    SDL_SetRenderTarget(renderer.Get(), nullptr);
}

void Background::renderBackground(Renderer& renderer) {
    // Copiar la textura del fondo en el renderer para cada frame
    renderer.Copy(backgroundTexture, SDL2pp::NullOpt, SDL2pp::NullOpt);
}
