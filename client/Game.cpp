#include "Background.h"
#include "Game.h"
#include <SDL2/SDL.h>
#include <exception>
#include <iostream>

Game::Game(ProtocoloCliente& protocol, BlockingQueue<uint8_t>& queue_sender, BlockingQueue<CommandGameShow>& queue_receiver)
        : graficos("DUCK GAME", 640, 480),
          duck(0.0, 386),
          background(graficos),
          prevTicks(SDL_GetTicks()),
          duckTexture (graficos.LoadTexture(DATA_PATH "/whiteDuck.png")) ,
          protocol(protocol),
          queue_sender(queue_sender),
          queue_receiver(queue_receiver) {}

void Game::run() {
    CommandGameShow command;
    dibujar(0, 386, STILL);

    while (true) try {
        unsigned int frameTicks = SDL_GetTicks();
        [[maybe_unused]]unsigned int frameDelta = frameTicks - prevTicks;
        prevTicks = frameTicks;

        correrHandlers();

        if (queue_receiver.try_pop(command)){
            for(auto &element : command.elements) {
                dibujar(element.x_pos, element.y_pos, element.typeOfMove);
            }
        }

        SDL_Delay(1);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        break;
    }
}

void Game::correrHandlers() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            throw std::runtime_error("Termino el juego");
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                case SDLK_q:
                    throw std::runtime_error("Termino el juego");
                case SDLK_d:
                    queue_sender.push(RIGTH);
                    break;
                case SDLK_a:
                    queue_sender.push(LEFT);
                    break;
                case SDLK_s:
                    queue_sender.push(DOWN);
                    break;
                case SDLK_w:
                    if (event.key.repeat==0) {
                        queue_sender.push(JUMP);

                    }

                    break;
            }
        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_d:
                    queue_sender.push(STILL);
                    break;
                case SDLK_a:
                    queue_sender.push(STILL);
                    break;
                case SDLK_s:
                    queue_sender.push(STILL);
                    break;

            }
        }
    }
}

void Game::dibujar(float posX, float posY, const uint8_t typeOfMove) {
    graficos.GetRenderer().Clear();
    background.draw(graficos.GetRenderer());
    duck.update(posY, posX);
    duck.draw(graficos.GetRenderer(), duckTexture, typeOfMove);
    graficos.GetRenderer().Present();
}
