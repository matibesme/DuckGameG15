#include "Background.h"
#include "Game.h"
#include <SDL2/SDL.h>
#include <exception>
#include <iostream>

Game::Game( BlockingQueue<uint8_t>& queue_sender, BlockingQueue<CommandGameShow>& queue_receiver)
        : graficos("DUCK GAME", 640, 480),
          duck(POSICION_INICIAL_X, POSICION_INICIAL_Y, graficos),
          background(graficos),
          queue_sender(queue_sender),
          queue_receiver(queue_receiver) {}

void Game::run() {
    try {
        Renderer& renderer = graficos.GetRenderer();
        CommandGameShow command;
        std::list<Bullet> bullets;
        dibujar(renderer, bullets);
        while (true) {
            correrHandlers();
            if (queue_receiver.try_pop(command)) {
                for (auto & personaje: command.lista_patos) {
                    duck.update(personaje.x_pos , personaje.y_pos, personaje.typeOfMove, personaje.typeOfGun);
                }
                bullets.clear();
                for (const auto& bullet_info : command.lista_balas) {
                    bullets.emplace_back(bullet_info.x_pos + DUCK_WIDTH, bullet_info.y_pos  + DUCK_HEIGHT / 2 , graficos, bullet_info.orientation, bullet_info.typeOfBullet);
                }

                dibujar(renderer, bullets);
            }
            SDL_Delay(1);
        }
    }catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        queue_sender.close();
    }
    graficos.GetRenderer().Clear();
}

void Game::dibujar(Renderer& renderer, std::list<Bullet>& bullets) {
    renderer.Clear();

    background.draw(renderer);
    duck.draw(renderer);
    for (auto& bullet : bullets) {
        bullet.draw(renderer);
    }

    renderer.Present();

}
void Game::correrHandlers() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_q:
                    throw std::runtime_error("Termino el juego");
            }
        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_d:
                case SDLK_a:
                case SDLK_s:
                case SDLK_w:
                case SDL_SCANCODE_SPACE:
                    queue_sender.push(STILL);
                    break;
            }
        } else if (event.type == SDL_QUIT) {
            throw std::runtime_error("Termino el juego");
        }
    }

    const Uint8 *estadoTeclas = SDL_GetKeyboardState(NULL);

    if (estadoTeclas[SDL_SCANCODE_D]) {
        queue_sender.push(RIGTH);
    } else if (estadoTeclas[SDL_SCANCODE_A]) {
        queue_sender.push(LEFT);
    } else if (estadoTeclas[SDL_SCANCODE_S]) {
        queue_sender.push(DOWN);
    }
    if (estadoTeclas[SDL_SCANCODE_W]) {
        queue_sender.push(JUMP);
    }
    //disparar con la tecla espacio
    if (estadoTeclas[SDL_SCANCODE_SPACE]) {
        queue_sender.push(SHOOT);
    }
}
