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
//VA A ANDAR PADRE
void Game::run() {
    CommandGameShow command;

    while (true) try {
        unsigned int frameTicks = SDL_GetTicks();
        [[maybe_unused]]unsigned int frameDelta = frameTicks - prevTicks;
        prevTicks = frameTicks;

        correrHandlers();

        graficos.GetRenderer().Clear();
        background.draw(graficos.GetRenderer());

        if(queue_receiver.try_pop(command)){
           for(auto &element : command.elements) {
               duck.update(element.y_pos, element.x_pos);
               duck.draw(graficos.GetRenderer(), duckTexture, element.typeOfMove);
           }
        } else{
            duck.draw(graficos.GetRenderer(), duckTexture, STILL);
        }
        graficos.GetRenderer().Present();

        SDL_Delay(1);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        break;
    }
}

//recibe por referencia
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

                    break;
                case SDLK_w:
                    if (duck.isTouchingFloor())

                        break;
            }
        }
    }
}
