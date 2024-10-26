#include "gameRunner.h"

GameRunner::GameRunner(BlockingQueue<uint8_t>& queue_sender, BlockingQueue<CommandGameShow>& queue_receiver)
        : graficos("DUCK GAME", 640, 480),
          gameRenderer(graficos),
          handler(queue_sender),
          queue_sender(queue_sender),
          queue_receiver(queue_receiver) {}

void GameRunner::run() {
    try {
        Renderer& sdl_renderer = graficos.GetRenderer();
        CommandGameShow command;
        std::list<Duck> ducks;
        std::list<Bullet> bullets;

        gameRenderer.dibujar(sdl_renderer, ducks, bullets);
        //REVISAR:
        //quiero cambiar de arma hardcodeando

        while (true) {
            handler.correrHandlers();
            if (queue_receiver.try_pop(command)) {
                actualizarElementos(command, ducks, bullets);
                gameRenderer.dibujar(sdl_renderer, ducks, bullets);
            }
            SDL_Delay(1);
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        queue_sender.close();
    }
    graficos.GetRenderer().Clear();
}

void GameRunner::actualizarElementos(const CommandGameShow& command, std::list<Duck>& ducks, std::list<Bullet>& bullets) {
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
                               [&duckStruct](const Duck& duck) {
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
}