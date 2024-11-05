#include "EventHandler.h"

EventHandler::EventHandler(BlockingQueue<uint8_t>& queue_sender)
        : queue_sender(queue_sender) {}

void EventHandler::correrHandlers() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                SDL_Keycode key = event.key.keysym.sym;
                if (teclas_presionadas.find(key) == teclas_presionadas.end()) {
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
                        case SDLK_LSHIFT:
                            queue_sender.push(SHOOT);  // Empieza a disparar
                            break;
                        case SDLK_f:
                            queue_sender.push(LEAVE_GUN);  // Soltar arma
                            break;
                        case SDLK_e:
                            queue_sender.push(PICKUP);  // Recoger objeto
                            break;
                        case SDLK_SPACE:
                            queue_sender.push(AIM_UP);  // Apuntar hacia arriba
                            break;
                    }
                }
                break;
            }
            case SDL_KEYUP: {
                SDL_Keycode key = event.key.keysym.sym;
                teclas_presionadas.erase(key);
                switch (key) {
                    case SDLK_a:
                        queue_sender.push(STILL_LEFT);
                        break;
                    case SDLK_d:
                        queue_sender.push(STILL_RIGHT);
                        break;
                    case SDLK_LSHIFT:
                        queue_sender.push(STOP_SHOOT);  // Detener disparo continuo
                        break;
                    case SDLK_SPACE:
                        queue_sender.push(STOP_AIM_UP);  // Dejar de apuntar arriba
                        break;
                }
                break;
            }
            case SDL_QUIT:
                throw std::runtime_error("Termino el juego");
        }
    }

    // Mover derecha e izquierda con teclas presionadas
    if (teclas_presionadas.find(SDLK_d) != teclas_presionadas.end()) {
        queue_sender.push(RIGHT);
    } else if (teclas_presionadas.find(SDLK_a) != teclas_presionadas.end()) {
        queue_sender.push(LEFT);
    }

    // Disparo continuo mientras SPACE esté presionado
    if (teclas_presionadas.find(SDLK_LSHIFT) != teclas_presionadas.end()) {
        queue_sender.push(SHOOT);
    }
}

