#include "Background.h"
#include "Game.h"
#include <SDL2/SDL.h>
#include <exception>
#include <iostream>

Game::Game()
        : graficos("SDL2pp demo", 640, 480),
          duck(0.0, 0.0),
          background(graficos),
          prevTicks(SDL_GetTicks()),
          duckTexture (graficos.LoadTexture(DATA_PATH "/duck.png")) {}

void Game::run() {
    SDL_Event event;

    bool isMovingRight = false, isMovingLeft = false, isOnFloor = false, is_jumping = false;

    while (true) {
        unsigned int frameTicks = SDL_GetTicks();
        unsigned int frameDelta = frameTicks - prevTicks;
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
                        isMovingRight = true;
                        break;
                    case SDLK_a:
                        isMovingLeft = true;
                        break;
                    case SDLK_s:
                        if (!duck.is_Jumping())
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

        duck.setOnFloor(isOnFloor);
        duck.update(isMovingRight, isMovingLeft, is_jumping, frameDelta);
        graficos.GetRenderer().Clear();
        background.draw(graficos.GetRenderer());
        duck.draw(graficos.GetRenderer(), duckTexture);
        graficos.GetRenderer().Present();

        SDL_Delay(1);
    }
}
