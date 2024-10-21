#include "Background.h"
#include "Game.h"
#include <SDL2/SDL.h>
#include <exception>
#include <iostream>

Game::Game(ProtocoloCliente& protocol, BlockingQueue<uint8_t>& queue_sender, BlockingQueue<CommandGameShow>& queue_receiver)
        : graficos("SDL2pp demo", 640, 480),
          duck(0.0, 0.0),
          background(graficos),
          prevTicks(SDL_GetTicks()),
          duckTexture (graficos.LoadTexture(DATA_PATH "/duck.png")) ,
          protocol(protocol),
          queue_sender(queue_sender),
          queue_receiver(queue_receiver) {}

void Game::run() {
    SDL_Event event;

    [[maybe_unused]]bool isMovingRight = false, isMovingLeft = false, isOnFloor = false, is_jumping = false;
    while (true) {
        unsigned int frameTicks = SDL_GetTicks();
        [[maybe_unused]]unsigned int frameDelta = frameTicks - prevTicks;
        prevTicks = frameTicks;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        return;
                    case SDLK_d:
                        //isMovingRight = true;
                        queue_sender.push(RIGTH);
                        break;
                    case SDLK_a:
                        isMovingLeft = true;
                        break;
                    case SDLK_s:
                        isOnFloor = true;
                        break;
                    case SDLK_w:
                        if (duck.isTouchingFloor())
                            is_jumping = true;
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_d:
                        isMovingRight = false;
                        break;
                    case SDLK_a:
                        isMovingLeft = false;
                        break;
                    case SDLK_s:
                        isOnFloor = false;
                        break;
                    case SDLK_w:
                        is_jumping = false;
                        break;
                }
            }
        }

        CommandGameShow command;

        if(queue_receiver.try_pop(command)){
           for(auto &element : command.elements) {
                duck.setPosicion(element.x_pos, element.y_pos);
           }
        }
        duck.setOnFloor(isOnFloor);
        duck.update(isMovingRight, isMovingLeft, is_jumping, frameDelta);
        graficos.GetRenderer().Clear();
        background.draw(graficos.GetRenderer());
        duck.draw(graficos.GetRenderer(), duckTexture);
        graficos.GetRenderer().Present();

        SDL_Delay(1);
    }
}
