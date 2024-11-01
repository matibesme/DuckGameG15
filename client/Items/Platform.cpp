#include <SDL_render.h>
#include "Platform.h"
#include "constant_definitons.h"

#define IMAGE_PLATAFORMA_CHICA DATA_PATH "/plataforma_prueba.png"
#define IMAGE_PLATAFORMA_GRANDE DATA_PATH "/plataforma_larga_prueba.png"

Platform::Platform( float initial_pos_x, float initial_pos_y, Graficos& graficos, uint8_t type
                    , float width, float height)
        : graficos(graficos), pos_x(initial_pos_x), pos_y(initial_pos_y), type(type), width(width), height(height) {}

void Platform::draw() {
    Renderer& renderer = graficos.GetRenderer();
    //creo una textura para dibujar las plataformas pero vacía porque no se puede dibujar directamente en la pantalla
    SDL2pp::Texture platform(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCENE_WIDTH, SCENE_HEIGHT);

    if (type == 1) {
        platform = graficos.LoadTexture(IMAGE_PLATAFORMA_GRANDE);
    } else {
        platform = graficos.LoadTexture(IMAGE_PLATAFORMA_CHICA);
    }

    SDL2pp::Rect destRect(pos_x, pos_y, width, height);
    renderer.Copy(platform, SDL2pp::NullOpt, destRect);
}

