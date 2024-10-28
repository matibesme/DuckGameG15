#include "GameRenderer.h"

GameRenderer::GameRenderer(Graficos& graficos)
        : graficos(graficos), background(graficos) {}

void GameRenderer::dibujar(Renderer& renderer, std::list<ClientDuck>& ducks, std::list<Bullet>& bullets,
                           std::list<Gun>& guns, [[maybe_unused]]std::list<Armor>& armors,[[maybe_unused]] std::list<Helmet>& helmets) {
    renderer.Clear();
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
    /*
    for (auto& armor : armors) {
        armor.draw(false, renderer);
    }
    for (auto& helmet : helmets) {
        helmet.draw(false, renderer);
    }*/

    renderer.Present();
}

void GameRenderer::actualizarElementos(const CommandGameShow& command, std::list<ClientDuck>& ducks,
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