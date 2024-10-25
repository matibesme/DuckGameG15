#include "Background.h"
#include "Game.h"
#include <SDL2/SDL.h>
#include <exception>
#include <iostream>
#include <unordered_set>

Game::Game(BlockingQueue<uint8_t>& queue_sender, BlockingQueue<CommandGameShow>& queue_receiver)
        : graficos("DUCK GAME", 640, 480),
          background(graficos),
          queue_sender(queue_sender),
          queue_receiver(queue_receiver) {}

void Game::run() {
    try {
        Renderer& renderer = graficos.GetRenderer();
        CommandGameShow command;
        std::list<Bullet> bullets;
        std::list<Duck> ducks;

        dibujar(renderer, ducks, bullets);

        while (true) {
            correrHandlers();
            if (queue_receiver.try_pop(command)) {
                //compruebo si el duck ya está en la lista, si no está lo agrego.
                for (const auto& duckStruct : command.lista_patos) {
                    auto it = std::find_if(ducks.begin(), ducks.end(),
                                           [&duckStruct](const Duck &duck) {
                                               return duck.getId() == duckStruct.id;
                                           });
                    if (it == ducks.end()) {
                        Duck new_duck(duckStruct.id, duckStruct.x_pos, duckStruct.y_pos, duckStruct.typeOfGun,
                                      duckStruct.direction, graficos);
                        ducks.push_back(std::move(new_duck));
                    } else {
                        // Si ya existe, cargarlo con los datos actuales
                        it->update(duckStruct.y_pos, duckStruct.x_pos, duckStruct.typeOfMove, duckStruct.typeOfGun);
                    }
                }

                // Compruebo si la bala ya está en la lista, si no está la agrego.
                for (const auto& bulletStruct : command.lista_balas) {
                    auto it = std::find_if(bullets.begin(), bullets.end(),
                                           [&bulletStruct](const Bullet& bullet) {
                                               return bullet.getId() == bulletStruct.id;
                                           });
                    if (it == bullets.end()) {
                        Bullet new_bullet(bulletStruct.id ,bulletStruct.x_pos, bulletStruct.y_pos, graficos, bulletStruct.orientation,
                                          bulletStruct.typeOfBullet);
                        bullets.push_back(std::move(new_bullet));
                    } else {
                        // Si ya existe, actualizarlo con los datos actuales
                        it->update(bulletStruct.x_pos, bulletStruct.y_pos, bulletStruct.typeOfBullet,
                                   bulletStruct.orientation);
                    }
                }

                dibujar(renderer, ducks, bullets);
            }
            SDL_Delay(1);
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        queue_sender.close();
    }
    graficos.GetRenderer().Clear();
}

void Game::dibujar(Renderer& renderer, std::list<Duck>& ducks, std::list<Bullet>& bullets) {
    renderer.Clear();

    background.draw(renderer);

    for (auto& duck : ducks) {
        duck.draw(renderer);
    }
    for (auto& bullet : bullets) {
        bullet.draw(renderer);
    }

    renderer.Present();
}

void Game::correrHandlers() {
    static std::unordered_set<SDL_Keycode> teclas_presionadas;  // Mantiene un registro de teclas actualmente presionadas
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                SDL_Keycode key = event.key.keysym.sym;
                if (teclas_presionadas.find(key) == teclas_presionadas.end()) {  // Solo procesa si la tecla no estaba presionada
                    teclas_presionadas.insert(key);
                    switch (key) {
                        case SDLK_q:
                            throw std::runtime_error("Termino el juego");
                        case SDLK_s:
                            queue_sender.push(DOWN);
                            break;
                        case SDLK_w:
                            queue_sender.push(JUMP);
                            break;
                        case SDLK_SPACE:
                            queue_sender.push(SHOOT);
                            break;
                        /*case SDLK_r:
                            queue_sender.push(CAMBIAR_ARMA);
                            break;*/
                    }
                }
                break;
            }
            case SDL_KEYUP: {
                SDL_Keycode key = event.key.keysym.sym;
                teclas_presionadas.erase(key);
                switch (key) {
                    case SDLK_a:
                        queue_sender.push(STILL_LEFT);  // Envía "STILL" al soltar las teclas de movimiento
                        break;
                    case SDLK_d:
                    case SDLK_SPACE:
                        queue_sender.push(STILL_RIGTH);  // Envía "STILL" al soltar las teclas de movimiento
                        break;
                    /*case SDLK_SPACE:
                        queue_sender.push(STOP_SHOOT);  // Detiene el disparo al soltar la barra espaciadora
                        break;*/
                }
                break;
            }
            case SDL_QUIT:
                throw std::runtime_error("Termino el juego");
        }
    }

    // Mantener el movimiento continuo hacia la derecha o izquierda si la tecla está presionada
    if (teclas_presionadas.find(SDLK_d) != teclas_presionadas.end()) {
        queue_sender.push(RIGTH);  // Movimiento hacia la derecha
    } else if (teclas_presionadas.find(SDLK_a) != teclas_presionadas.end()) {
        queue_sender.push(LEFT);   // Movimiento hacia la izquierda
    }
}
