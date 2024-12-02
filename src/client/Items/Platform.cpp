#include "Platform.h"

#include <SDL_render.h>

#include "../common/common_constant.h"
#include "constantTextures.h"

Platform::Platform(float initial_pos_x, float initial_pos_y, Graficos &graficos,
                   uint8_t type, float width, float height)
    : graficos(graficos), pos_x(initial_pos_x), pos_y(initial_pos_y),
      type(type), width(width), height(height) {}

void Platform::draw() {
    Renderer &renderer = graficos.GetRenderer();
    SDL2pp::Texture *platform = nullptr;

    // Crear un mapa para asociar el tipo de plataforma a las imágenes
    static const std::map<int, const char*> platformTextures = {
            {TYPE_PLATFORM_DONUT, IMAGE_PLATAFORMA_DONUT},
            {TYPE_PLATFORM_INDUSTRIAL, IMAGE_PLATAFORMA_INDUSTRIAL},
            {TYPE_PLATFORM_NATURE, IMAGE_PLATAFORMA_NATURE},
            {TYPE_PLATFORM_SPACE, IMAGE_PLATAFORMA_SPACE},
            {TYPE_PLATFORM_UNDERGROUND, IMAGE_PLATAFORMA_UNDERGROUND},
            {TYPE_PLATFORM_DONUT_LONG, IMAGE_PLATAFORMA_DONUT_LONG},
            {TYPE_PLATFORM_NATURE_LONG, IMAGE_PLATAFORMA_NATURE_LONG},
            // walls
            {TYPE_WALL_DONUT, IMAGE_WALL_DONUT},
            {TYPE_WALL_NATURE, IMAGE_WALL_NATURE},
            {TYPE_WALL_UNDERGROUND, IMAGE_WALL_UNDERGROUND}
    };

    // Buscar la textura correspondiente en el mapa
    auto it = platformTextures.find(type);
    if (it != platformTextures.end()) {
        platform = &graficos.getTexture(it->second); // Asignar la textura
    }

    if (platform != nullptr) {
        SDL2pp::Rect destRect(pos_x, pos_y, width, height);
        renderer.Copy(*platform, SDL2pp::NullOpt, destRect);
    }
}

float Platform::getX() { return pos_x; }

float Platform::getY() { return pos_y; }
