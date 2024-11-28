#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <string>
#include <memory>

class TextureManager {
public:
    TextureManager(SDL2pp::Renderer &renderer);

    // Obtener una textura por su ID
    SDL2pp::Texture &getTexture(uint8_t id);

private:
    // Cargar todas las texturas
    void loadTextures();

    SDL2pp::Renderer &renderer;
    // Mapas para gestionar texturas y sus rutas
    std::map<uint8_t, std::string> textures;
};

#endif // TEXTURE_MANAGER_H
