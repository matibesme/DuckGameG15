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
                    // Controles para Jugador 1
                    switch (key) {
                        case SDLK_q:
                            throw std::runtime_error("Termino el juego");
                        case SDLK_s:
                            queue_sender.push(DOWN_J1);
                            break;
                        case SDLK_w:
                            queue_sender.push(JUMP_J1);
                            break;
                        case SDLK_LSHIFT:
                            queue_sender.push(SHOOT_J1);  // Empieza a disparar
                            break;
                        case SDLK_f:
                            queue_sender.push(LEAVE_GUN_J1);  // Soltar arma
                            break;
                        case SDLK_e:
                            queue_sender.push(PICKUP_J1);  // Recoger objeto
                            break;
                        case SDLK_SPACE:
                            queue_sender.push(AIM_UP_J1);  // Apuntar hacia arriba
                            break;

                            // Controles para Jugador 2
                        case SDLK_k:
                            queue_sender.push(DOWN_J2);
                            break;
                        case SDLK_i:
                            queue_sender.push(JUMP_J2);
                            break;
                        case SDLK_RSHIFT:
                            queue_sender.push(SHOOT_J2);  // Empieza a disparar
                            break;
                        case SDLK_h:
                            queue_sender.push(LEAVE_GUN_J2);  // Soltar arma
                            break;
                        case SDLK_u:
                            queue_sender.push(PICKUP_J2);  // Recoger objeto
                            break;
                        case SDLK_RETURN:
                            queue_sender.push(AIM_UP_J2);  // Apuntar hacia arriba
                            break;
                    }
                }
                break;
            }
            case SDL_KEYUP: {
                SDL_Keycode key = event.key.keysym.sym;
                teclas_presionadas.erase(key);
                // Controles para Jugador 1
                switch (key) {
                    case SDLK_a:
                        queue_sender.push(STILL_LEFT_J1);
                        break;
                    case SDLK_d:
                        queue_sender.push(STILL_RIGHT_J1);
                        break;
                    case SDLK_LSHIFT:
                        queue_sender.push(STOP_SHOOT_J1);  // Detener disparo continuo
                        break;
                    case SDLK_SPACE:
                        queue_sender.push(STOP_AIM_UP_J1);  // Dejar de apuntar arriba
                        break;

                        // Controles para Jugador 2
                    case SDLK_j:
                        queue_sender.push(STILL_LEFT_J2);
                        break;
                    case SDLK_l:
                        queue_sender.push(STILL_RIGHT_J2);
                        break;
                    case SDLK_RSHIFT:
                        queue_sender.push(STOP_SHOOT_J2);  // Detener disparo continuo
                        break;
                    case SDLK_RETURN:
                        queue_sender.push(STOP_AIM_UP_J2);  // Dejar de apuntar arriba
                        break;
                }
                break;
            }
            case SDL_QUIT:
                throw std::runtime_error("Termino el juego");
        }
    }

    // Mover derecha e izquierda con teclas presionadas para Jugador 1
    if (teclas_presionadas.find(SDLK_d) != teclas_presionadas.end()) {
        queue_sender.push(RIGHT_J1);
    } else if (teclas_presionadas.find(SDLK_a) != teclas_presionadas.end()) {
        queue_sender.push(LEFT_J1);
    }

    // Mover derecha e izquierda con teclas presionadas para Jugador 2
    if (teclas_presionadas.find(SDLK_l) != teclas_presionadas.end()) {
        queue_sender.push(RIGHT_J2);
    } else if (teclas_presionadas.find(SDLK_j) != teclas_presionadas.end()) {
        queue_sender.push(LEFT_J2);
    }

    // Disparo continuo mientras las teclas de disparo estén presionadas
    if (teclas_presionadas.find(SDLK_LSHIFT) != teclas_presionadas.end()) {
        queue_sender.push(SHOOT_J1);
    }
    if (teclas_presionadas.find(SDLK_RSHIFT) != teclas_presionadas.end()) {
        queue_sender.push(SHOOT_J2);
    }
}

