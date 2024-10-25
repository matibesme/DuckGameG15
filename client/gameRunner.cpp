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
        //Por que el pato no se queda quieto
        //La imagen del pato cuando se agacha es otra
        //Tener en cuenta mas imagenes en cuanto a las armas y balas

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
    // Actualizar patos según el comando
    for (const auto& duckStruct : command.lista_patos) {
        auto it = std::find_if(ducks.begin(), ducks.end(),
                               [&duckStruct](const Duck &duck) {
                                   return duck.getId() == duckStruct.id;
                               });
        if (it == ducks.end()) {
            ducks.emplace_back(duckStruct.id, duckStruct.x_pos, duckStruct.y_pos, duckStruct.typeOfGun, duckStruct.typeOfMove, graficos);
        } else {
            it->update(duckStruct.y_pos, duckStruct.x_pos, duckStruct.typeOfMove, duckStruct.typeOfGun);
        }
    }

    // Actualizar balas según el comando
    for (const auto& bulletStruct : command.lista_balas) {
        auto it = std::find_if(bullets.begin(), bullets.end(),
                               [&bulletStruct](const Bullet& bullet) {
                                   return bullet.getId() == bulletStruct.id;
                               });
        if (it == bullets.end()) {
            bullets.emplace_back(bulletStruct.id ,bulletStruct.x_pos, bulletStruct.y_pos, graficos, bulletStruct.orientation,
                                 bulletStruct.typeOfBullet);
        } else {
            it->update(bulletStruct.x_pos, bulletStruct.y_pos, bulletStruct.typeOfBullet, bulletStruct.orientation);
        }
    }
}
