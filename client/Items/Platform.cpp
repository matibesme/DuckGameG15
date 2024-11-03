#include <SDL_render.h>
#include "Platform.h"
#include "../common/common_constant.h"

#define IMAGE_PLATAFORMA_DONUT DATA_PATH "/platform/Donut.png"
#define IMAGE_PLATAFORMA_INDUSTRIAL DATA_PATH "/platform/Industrial.png"
#define IMAGE_PLATAFORMA_NATURE DATA_PATH "/platform/Nature.png"
#define IMAGE_PLATAFORMA_SPACE DATA_PATH "/platform/Space.png"
#define IMAGE_PLATAFORMA_UNDERGROUND DATA_PATH "/platform/Underground.png"

Platform::Platform( float initial_pos_x, float initial_pos_y, Graficos& graficos, uint8_t type
                    , float width, float height)
        : graficos(graficos), pos_x(initial_pos_x), pos_y(initial_pos_y), type(type), width(width), height(height) {}

void Platform::draw() {
    Renderer& renderer = graficos.GetRenderer();
    //creo una textura para dibujar las plataformas pero vacía porque no se puede dibujar directamente en la pantalla
    SDL2pp::Texture platform(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCENE_WIDTH, SCENE_HEIGHT);

    switch (type) {
        case TYPE_PLATFORM_DONUT:
            platform = graficos.LoadTexture(IMAGE_PLATAFORMA_DONUT);
            break;
        case TYPE_PLATFORM_INDUSTRIAL:
            platform = graficos.LoadTexture(IMAGE_PLATAFORMA_INDUSTRIAL);
            break;
        case TYPE_PLATFORM_NATURE:
            platform = graficos.LoadTexture(IMAGE_PLATAFORMA_NATURE);
            break;
        case TYPE_PLATFORM_SPACE:
            platform = graficos.LoadTexture(IMAGE_PLATAFORMA_SPACE);
            break;
        case TYPE_PLATFORM_UNDERGROUND:
            platform = graficos.LoadTexture(IMAGE_PLATAFORMA_UNDERGROUND);
            break;
    }

    SDL2pp::Rect destRect(pos_x, pos_y, width, height);
    renderer.Copy(platform, SDL2pp::NullOpt, destRect);
}

