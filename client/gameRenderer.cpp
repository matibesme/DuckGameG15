#include <SDL_render.h>
#include <SDL_image.h>
#include "GameRenderer.h"

GameRenderer::GameRenderer(Graficos& graficos, Background& background)
        : graficos(graficos), background(background) {}
/*
void GameRenderer::dibujar(Renderer& renderer, std::list<ClientDuck>& ducks, std::list<Bullet>& bullets,
                           std::list<Gun>& guns, [[maybe_unused]]std::list<Armor>& armors,[[maybe_unused]] std::list<Helmet>& helmets) {
    renderer.Clear();

    //dibujar sobre una textura del tamñano del mapa le hago un zoom mas un clip
    //y eso se lo paso al render 64x64
    //dibujo todo solo muestro un poco
    // Renderiza el fondo y las plataformas ya cargadas anteriormente
    // background.renderBackground(renderer);
    background.draw(renderer);

    for (auto& duck : ducks) {
        duck.draw(renderer);
    }
    for (auto& bullet : bullets) {
        bullet.draw(renderer);
    }
    for (auto& gun : guns) {
        gun.draw(false, renderer);
    }

    for (auto& armor : armors) {
        armor.draw(false, renderer);
    }
    for (auto& helmet : helmets) {
        helmet.draw(false, renderer);
    }

    //dibujo la textura al render y luego present
    renderer.Present();
}*/

void GameRenderer::dibujar(Renderer& renderer, [[maybe_unused]] std::list<ClientDuck>& ducks,
                           [[maybe_unused]] std::list<Bullet>& bullets,
                           [[maybe_unused]] std::list<Gun>& guns,
                           [[maybe_unused]] std::list<Armor>& armors,
                           [[maybe_unused]] std::list<Helmet>& helmets) {
    // Crear una textura de 640x480
    SDL2pp::Texture textureDeTodo(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 640, 480);

    // Render apunta a la nueva textura creada
    renderer.SetTarget(textureDeTodo);
    // Limpio lo que tenía la textura
    renderer.Clear();

    // Quiero añadir el fondo y las plataformas a la textura
    background.draw(renderer);
    ClientDuck& duckRef = ducks.front();

    for (auto& duck : ducks) {
        duck.draw(renderer);
    }

    // Volver al render por defecto
    renderer.SetTarget();

    // Limpiar el renderer
    renderer.Clear();

    /* Definir el área de zoom (puedes ajustar estos valores para elegir una parte aleatoria)
    int zoomX = 50; // Coordenada X de la parte que quieres mostrar
    int zoomY = 400; // Coordenada Y de la parte que quieres mostrar
    int zoomWidth = 200; // Ancho de la parte a mostrar
    int zoomHeight = 200; // Alto de la parte a mostrar*/

    int zoomX = duckRef.getPosX()- 100 + DUCK_WIDTH / 2;
    int zoomY = duckRef.getPosY() - 100 + DUCK_HEIGHT / 2;
    int zoomWidth = 200; // Ancho de la parte a mostrar
    int zoomHeight = 200; // Alto de la parte a mostrar*

    // srcRect es el rectángulo que se tomará de la textura
    SDL2pp::Rect srcRect(zoomX, zoomY, zoomWidth, zoomHeight);

    /* Definir rectángulo de destino (toda la ventana)
    SDL2pp::Rect destRect(0, 0, 640, 480); // Cambiar a 800x600 para llenar la ventana

    // Calcular el factor de escala
    float scaleX = static_cast<float>(destRect.w) / srcRect.w; // Escala en X
    float scaleY = static_cast<float>(destRect.h) / srcRect.h; // Escala en Y

    // Asegúrate de que el rectángulo de destino tenga el tamaño adecuado para el zoom
    destRect.w = static_cast<int>(zoomWidth * scaleX);
    destRect.h = static_cast<int>(zoomHeight * scaleY);*/

    // Renderizar la textura con zoom, aplicando la escala
    renderer.Copy(textureDeTodo, SDL2pp::Optional<SDL2pp::Rect>(srcRect), SDL2pp::Optional<SDL2pp::Rect>());

    // Presentar el renderizado
    renderer.Present();
}


void GameRenderer::actualizarElementos(const GameState& command, std::list<ClientDuck>& ducks,
                                       std::list<Bullet>& bullets, std::list<Gun>& weapons,
                                       [[maybe_unused]]std::list<Armor>& armors, [[maybe_unused]]std::list<Helmet>& helmets) {
    //PRIMERO ACTUALIZO PATOS
    // Actualizar y eliminar patos
    for (auto it = ducks.begin(); it != ducks.end();) {
        auto duckInCommand = std::find_if(command.lista_patos.begin(), command.lista_patos.end(),
                                          [it](const DTODuck& duckStruct) {
                                              return duckStruct.id == it->getId();
                                          });
        if (duckInCommand != command.lista_patos.end()) {
            // Actualizar si el pato está en ambas listas
            it->update(duckInCommand->y_pos, duckInCommand->x_pos, duckInCommand->typeOfMove, duckInCommand->typeOfGun);
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
        auto bulletInCommand = std::find_if(command.lista_balas.begin(), command.lista_balas.end(),
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
            bullets.emplace_back(bulletStruct.id, bulletStruct.x_pos, bulletStruct.y_pos, graficos, bulletStruct.orientation,
                                 bulletStruct.typeOfBullet);
        }
    }

    //TERCERO ACTUALIZO ARMAS
    for (auto it = weapons.begin(); it != weapons.end();) {
        auto weaponInCommand = std::find_if(command.lista_guns.begin(), command.lista_guns.end(),
                                            [it](const DTOGuns& weaponStruct) {
                                                return weaponStruct.x_pos == it->getPosX() && weaponStruct.y_pos == it->getPosY();
                                            });
        if (weaponInCommand != command.lista_guns.end()) {
            // Actualizar si el arma está en ambas listas
            ++it;
        } else {
            // Eliminar si solo está en la lista local
            it = weapons.erase(it);
        }
    }

    // Agregar armas que están en el comando pero no en la lista local
    for (const auto& weaponStruct : command.lista_guns) {
        auto it = std::find_if(weapons.begin(), weapons.end(),
                               [&weaponStruct](Gun& weapon) {
                                   return weapon.getPosX() == weaponStruct.x_pos && weapon.getPosY() == weaponStruct.y_pos;
                               });
        if (it == weapons.end()) {
            weapons.emplace_back(graficos, weaponStruct.x_pos, weaponStruct.y_pos, weaponStruct.typeOfGun);
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
}
