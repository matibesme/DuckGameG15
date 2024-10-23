#include "Background.h"
#include "Game.h"
#include <SDL2/SDL.h>
#include <exception>
#include <iostream>

Game::Game(ProtocoloCliente& protocol, BlockingQueue<uint8_t>& queue_sender, BlockingQueue<CommandGameShow>& queue_receiver)
        : graficos("DUCK GAME", 640, 480),
          duck(POSICION_INICIAL_X, POSICION_INICIAL_Y),
          background(graficos),
          prevTicks(SDL_GetTicks()),
          duckTexture (graficos.LoadTexture(DATA_PATH "/whiteDuck.png")) ,
          protocol(protocol),
          queue_sender(queue_sender),
          queue_receiver(queue_receiver) {}

void Game::run() {
    Renderer& renderer = graficos.GetRenderer();
    CommandGameShow command;
    dibujar(POSICION_INICIAL_X, POSICION_INICIAL_Y, STILL, renderer);
    try {
        while (1) {
            correrHandlers();
            if (queue_receiver.try_pop(command)) {
                for (auto &element: command.elements) {
                    dibujar(element.x_pos, element.y_pos, element.typeOfMove, renderer);
                }
            }
            SDL_Delay(1);
        }
    }catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        queue_sender.close();
    }
    graficos.GetRenderer().Clear();
}
void Game::correrHandlers() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                case SDLK_q:
                    throw std::runtime_error("Termino el juego");
            }
        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_d:
                case SDLK_a:
                case SDLK_s:
                case SDLK_w:
                    queue_sender.push(STILL);
                    break;
            }
        } else if (event.type == SDL_QUIT) {
            throw std::runtime_error("Termino el juego");
        }
    }

    const Uint8* estadoTeclas = SDL_GetKeyboardState(NULL);

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
}



void Game::dibujar(float posX, float posY, const uint8_t typeOfMove, Renderer& renderer) {
    renderer.Clear();
    background.draw(renderer);
    duck.update(posY, posX);
    duck.draw(renderer, duckTexture, typeOfMove);
    renderer.Present();
}
