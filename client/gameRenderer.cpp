#include <SDL_render.h>
#include "GameRenderer.h"
#include <algorithm> // para std::min y std::max

#define IMAGE_CIELO_NUBES DATA_PATH "/cielo_nubes.jpg"
#define IMAGE_CITY DATA_PATH "/backgrounds/City.png"
#define IMAGE_FOREST DATA_PATH "/backgrounds/Forest.png"

#define CANT_ZOOM_WIDTH (10 * DUCK_WIDTH)
#define CANT_ZOOM_HEIGHT (10 * DUCK_HEIGHT)

GameRenderer::GameRenderer(Graficos& graficos, std::list<DTOPlatform>& platform, std::list<DTOBoxes>& box)
                : graficos(graficos){
    // Creo las plataformas por única vez
    for (auto& platformStruct : platform) {
        platforms.emplace_back(platformStruct.x_pos, platformStruct.y_pos, graficos,  platformStruct.type,
                               platformStruct.width, platformStruct.height);
    }

    // Creo las cajas por única vez
    for (auto& boxStruct : box) {
        boxes.emplace_back(boxStruct.id, boxStruct.x_pos, boxStruct.y_pos, graficos);
    }
}

void GameRenderer::dibujar(Renderer& renderer, GameState& command) {
    // Limpio el renderizador y dibujar el fondo directamente en la pantalla
    renderer.SetTarget();
    renderer.Clear();
    drawBackground(command.backGround_id);

    // Creo una textura para dibujar todos los objetos
    SDL2pp::Texture textureDeTodo(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCENE_WIDTH,
                                  SCENE_HEIGHT);

    // Habilito blending en la textura
    textureDeTodo.SetBlendMode(SDL_BLENDMODE_BLEND);

    // Cambio el objetivo de renderizado a textureDeTodo
    renderer.SetTarget(textureDeTodo);
    renderer.SetDrawColor(0, 0, 0, 0); // Limpio la textura con un color transparente
    renderer.Clear();

    // Dibujo los objetos en la textura
    for (auto& box : boxes) box.draw(renderer);
    for (auto& platform : platforms) platform.draw();
    for (auto& duck : ducks) duck.draw(renderer);
    for (auto& bullet : bullets) bullet.draw(renderer);
    for (auto& gun : guns) gun.draw(false, renderer);

    // Vuelve al render principal
    renderer.SetTarget();

    /*//DESCOMENTAR PARA TENER ZOOM
    // Defino el rectángulo de zoom para centrarse en la posición deseada
    SDL2pp::Rect srcRect = calcularRectanguloDeZoom(ducks); // Método que calcula el rectángulo para incluir todos los patos
    // Renderizar la textura con los objetos y zoom, sobre el fondo
    renderer.Copy(textureDeTodo, SDL2pp::Optional<SDL2pp::Rect>(srcRect), SDL2pp::Optional<SDL2pp::Rect>());*/

    //Por ahora no hago zoom
    renderer.Copy(textureDeTodo, SDL2pp::Optional<SDL2pp::Rect>(), SDL2pp::Optional<SDL2pp::Rect>());

    renderer.Present();
}

void GameRenderer::actualizarElementos(const GameState& command) {
    //PRIMERO ACTUALIZO PATOS
    // Actualizar y eliminar patos
    for (auto it = ducks.begin(); it != ducks.end();) {
        auto duckInCommand = std::find_if(command.lista_patos.begin(),
                                          command.lista_patos.end(),
                                          [it](const DTODuck& duckStruct) {
                                              return duckStruct.id == it->getId();
                                          });
        if (duckInCommand != command.lista_patos.end()) {
            // Actualizar si el pato está en ambas listas
            it->update(duckInCommand->y_pos, duckInCommand->x_pos, duckInCommand->typeOfMove,
                       duckInCommand->typeOfGun);
            ++it;
        } else {
            // Eliminar si solo está en la lista local
            it = ducks.erase(it);
        }
    }

    // Agregar patos que están en el comando pero no en la lista local
    for (const auto& duckStruct : command.lista_patos) {
        auto it = std::find_if(ducks.begin(), ducks.end(),
                               [&duckStruct](const ClientDuck& duck) {
                                   return duck.getId() == duckStruct.id;
                               });
        if (it == ducks.end()) {
            ducks.emplace_back(duckStruct.id, duckStruct.x_pos, duckStruct.y_pos, duckStruct.typeOfGun,
                               duckStruct.typeOfMove, graficos);
        }
    }

    //SEGUNDO ACTUALIZO BALAS
    // Actualizar y eliminar balas
    for (auto it = bullets.begin(); it != bullets.end();) {
        auto bulletInCommand = std::find_if(command.lista_balas.begin(),
                                            command.lista_balas.end(),
                                            [it](const DTOBullet& bulletStruct) {
                                                return bulletStruct.id == it->getId();
                                            });
        if (bulletInCommand != command.lista_balas.end()) {
            // Actualizar si la bala está en ambas listas
            it->update(bulletInCommand->x_pos, bulletInCommand->y_pos, bulletInCommand->typeOfBullet,
                       bulletInCommand->orientation);
            ++it;
        } else {
            // Eliminar si solo está en la lista local
            it = bullets.erase(it);
        }
    }

    // Agregar balas que están en el comando pero no en la lista local
    for (const auto& bulletStruct : command.lista_balas) {
        auto it = std::find_if(bullets.begin(), bullets.end(),
                               [&bulletStruct](const Bullet& bullet) {
                                   return bullet.getId() == bulletStruct.id;
                               });
        if (it == bullets.end()) {
            bullets.emplace_back(bulletStruct.id, bulletStruct.x_pos, bulletStruct.y_pos, graficos,
                                 bulletStruct.orientation,
                                 bulletStruct.typeOfBullet);
        }
    }

    //TERCERO ACTUALIZO ARMAS
    for (auto it = guns.begin(); it != guns.end();) {
        auto weaponInCommand = std::find_if(command.lista_guns.begin(),
                                            command.lista_guns.end(),
                                            [it](const DTOGuns& weaponStruct) {
                                                return weaponStruct.x_pos == it->getPosX()
                                                && weaponStruct.y_pos == it->getPosY();
                                            });
        if (weaponInCommand != command.lista_guns.end()) {
            // Actualizar si el arma está en ambas listas
            ++it;
        } else {
            // Eliminar si solo está en la lista local
            it = guns.erase(it);
        }
    }

    // Agregar armas que están en el comando pero no en la lista local
    for (const auto& weaponStruct : command.lista_guns) {
        auto it = std::find_if(guns.begin(), guns.end(),
                               [&weaponStruct](Gun& weapon) {
                                   return weapon.getPosX() == weaponStruct.x_pos
                                   && weapon.getPosY() == weaponStruct.y_pos;
                               });
        if (it == guns.end()) {
            guns.emplace_back(graficos, weaponStruct.x_pos, weaponStruct.y_pos, weaponStruct.typeOfGun);
        }
    }

    /*
    //CUARTO ACTUALIZO ARMADURAS
    for (auto it = armors.begin(); it != armors.end();) {
        auto armorInCommand = std::find_if(command.lista_armors.begin(), command.lista_armors.end(),
                                            [it](const DTOArmor& armorStruct) {
                                                return armorStruct.x_pos == it->getPosX() && armorStruct.y_pos == it->getPosY();
                                            });
        if (armorInCommand != command.lista_armors.end()) {
            // Actualizar si el arma está en ambas listas
            ++it;
        } else {
            // Eliminar si solo está en la lista local
            it = armors.erase(it);
        }
    }

    // Agregar armaduras que están en el comando pero no en la lista local
    for (const auto& armorStruct : command.lista_armors) {
        auto it = std::find_if(armors.begin(), armors.end(),
                               [&armorStruct](Armor& armor) {
                                   return armor.getPosX() == armorStruct.x_pos && armor.getPosY() == armorStruct.y_pos;
                               });
        if (it == armors.end()) {
            armors.emplace_back(graficos, armorStruct.x_pos, armorStruct.y_pos);
        }
    }

    //QUINTO ACTUALIZO CASCOS
    for (auto it = helmets.begin(); it != helmets.end();) {
        auto helmetInCommand = std::find_if(command.lista_helmets.begin(), command.lista_helmets.end(),
                                            [it](const DTOHelmet& helmetStruct) {
                                                return helmetStruct.x_pos == it->getPosX() && helmetStruct.y_pos == it->getPosY();
                                            });
        if (helmetInCommand != command.lista_helmets.end()) {
            // Actualizar si el arma está en ambas listas
            ++it;
        } else {
            // Eliminar si solo está en la lista local
            it = helmets.erase(it);
        }
    }

    // Agregar cascos que están en el comando pero no en la lista local
    for (const auto& helmetStruct : command.lista_helmets) {
        auto it = std::find_if(helmets.begin(), helmets.end(),
                               [&helmetStruct](Helmet& helmet) {
                                   return helmet.getPosX() == helmetStruct.x_pos && helmet.getPosY() == helmetStruct.y_pos;
                               });
        if (it == helmets.end()) {
            helmets.emplace_back(graficos, helmetStruct.x_pos, helmetStruct.y_pos);
        }
    }*/

    //SEXTO ACTUALIZO CAJAS
    for (auto it = boxes.begin(); it != boxes.end();) {
        auto boxInCommand = std::find_if(command.lista_boxes.begin(),
                                         command.lista_boxes.end(),
                                            [it](const DTOBoxes& boxStruct) {
                                                return boxStruct.id == it->getId();
                                            });
        if (boxInCommand != command.lista_boxes.end()) {
            // Actualizar si la caja está en ambas listas
            ++it;
        } else {
            // Eliminar si solo está en la lista local
            it = boxes.erase(it);
        }
    }

    // Agregar cajas que están en el comando pero no en la lista local
    for (const auto& boxStruct : command.lista_boxes) {
        auto it = std::find_if(boxes.begin(), boxes.end(),
                               [&boxStruct](Box& box) {
                                   return box.getId() == boxStruct.id;
                               });
        if (it == boxes.end()) {
            boxes.emplace_back(boxStruct.id, boxStruct.x_pos, boxStruct.y_pos, graficos);
        }
    }


}

void GameRenderer::drawBackground(const uint8_t background_id) {
    Renderer& renderer = graficos.GetRenderer();

    //creo una textura vacía para dibujar el fondo
    SDL2pp::Texture background (renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCENE_WIDTH, SCENE_HEIGHT);

    // Cargar y dibujar el fondo
    if (background_id == TYPE_BACKGROUND_CIELO_NUBES) {
        background = graficos.LoadTexture(IMAGE_CIELO_NUBES);
    } else if (background_id == TYPE_BACKGROUND_CITY) {
        background = graficos.LoadTexture(IMAGE_CITY);
    } else if (background_id == TYPE_BACKGROUND_FOREST) {
        background = graficos.LoadTexture(IMAGE_FOREST);
    }

    renderer.Copy(background, SDL2pp::NullOpt, SDL2pp::NullOpt);
}

SDL2pp::Rect GameRenderer::calcularRectanguloDeZoom( std::list<ClientDuck>& ducks) {
    if (ducks.empty()) {
        return {0, 0, 0, 0};
    }

    // Inicializo valores extremos con el primer pato
    int minX = ducks.front().getPosX();
    int maxX = minX;
    int minY = ducks.front().getPosY();
    int maxY = minY;

    // Encuentra las posiciones mínimas y máximas de los patos
    for ( auto& duck : ducks) {
        minX = std::min(minX, duck.getPosX());
        maxX = std::max(maxX, duck.getPosX());
        minY = std::min(minY, duck.getPosY());
        maxY = std::max(maxY, duck.getPosY());
    }

    // Calculo el ancho y alto del rectángulo para cubrir todos los patos
    int zoomWidth = maxX - minX + DUCK_WIDTH + CANT_ZOOM_WIDTH;
    int zoomHeight = maxY - minY + DUCK_HEIGHT + CANT_ZOOM_HEIGHT;

    return {minX - CANT_ZOOM_WIDTH / 2, minY - CANT_ZOOM_HEIGHT / 2, zoomWidth, zoomHeight};
}
