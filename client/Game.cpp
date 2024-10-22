#include "Background.h"
#include "Game.h"
#include <SDL2/SDL.h>
#include <exception>
#include <iostream>

Game::Game(ProtocoloCliente& protocol, BlockingQueue<uint8_t>& queue_sender, BlockingQueue<CommandGameShow>& queue_receiver)
        : graficos("SDL2pp demo", 640, 480),
          duck(0.0, 386),
          background(graficos),
          prevTicks(SDL_GetTicks()),
          duckTexture (graficos.LoadTexture(DATA_PATH "/duck.png")) ,
          protocol(protocol),
          queue_sender(queue_sender),
          queue_receiver(queue_receiver) {}

void Game::run() {
    CommandGameShow command;
    graficos.GetRenderer().Clear();
    background.draw(graficos.GetRenderer());
    duck.draw(graficos.GetRenderer(), duckTexture, STILL);
    graficos.GetRenderer().Present();

    while (true) try {
        unsigned int frameTicks = SDL_GetTicks();
        [[maybe_unused]]unsigned int frameDelta = frameTicks - prevTicks;
        prevTicks = frameTicks;

        correrHandlers();

        if (queue_receiver.try_pop(command)){
            for(auto &element : command.elements) {
                graficos.GetRenderer().Clear();
                background.draw(graficos.GetRenderer());
                duck.update(element.y_pos, element.x_pos);
                duck.draw(graficos.GetRenderer(), duckTexture, element.typeOfMove);
                graficos.GetRenderer().Present();
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
                    return;
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
                    if (duck.isTouchingFloor())

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
                case SDLK_w:
                    queue_sender.push(STILL);
                    break;
            }
        }
    }
}
