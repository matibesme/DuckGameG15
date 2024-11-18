#include "EventHandler.h"

EventHandler::EventHandler(BlockingQueue<ClientAction> &queue_sender)
    : queue_sender(queue_sender) {}

void EventHandler::correrHandlers() {
  SDL_Event event;
  ClientAction action{};
  action.player = 1;
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
          action.type_of_movement = DOWN;
          queue_sender.push(action);
          break;
        case SDLK_w:
          action.type_of_movement = JUMP;
          queue_sender.push(action);
          break;
        case SDLK_LSHIFT:
          action.type_of_movement = SHOOT;
          queue_sender.push(action); // Empieza a disparar
          break;
        case SDLK_f:
          action.type_of_movement = LEAVE_GUN;
          queue_sender.push(action); // Soltar arma
          break;
        case SDLK_e:
          action.type_of_movement = PICKUP;
          queue_sender.push(action); // Recoger objeto
          break;
        case SDLK_SPACE:
          action.type_of_movement = AIM_UP;
          queue_sender.push(action); // Apuntar hacia arriba
          break;

          // Controles para Jugador 2
        case SDLK_k:
          action.type_of_movement = DOWN;
          action.player = 2;
          queue_sender.push(action);
          break;
        case SDLK_i:
          action.type_of_movement = JUMP;
          action.player = 2;
          queue_sender.push(action);
          break;
        case SDLK_RSHIFT:
          action.type_of_movement = SHOOT;
          action.player = 2;
          queue_sender.push(action); // Empieza a disparar
          break;
        case SDLK_h:
          action.type_of_movement = LEAVE_GUN;
          action.player = 2;
          queue_sender.push(action); // Soltar arma
          break;
        case SDLK_u:
          action.type_of_movement = PICKUP;
          action.player = 2;
          queue_sender.push(action); // Recoger objeto
          break;
        case SDLK_m:
          action.type_of_movement = AIM_UP;
          action.player = 2;
          queue_sender.push(action); // Apuntar hacia arriba
          break;

        // controles cheats
        case SDLK_2:
          action.type_of_movement = CHEAT_CHANGE_WEAPON; // Cambio de arma
          queue_sender.push(action);                     // Jugador 1
          break;
        case SDLK_8:
          action.type_of_movement = CHEAT_CHANGE_WEAPON; // Cambio de arma
          action.player = 2;                             // Jugador 2
          queue_sender.push(action);
          break;
        case SDLK_b:
          action.type_of_movement = CHEAT_SPAWN_BOX; // Spawnear caja
          queue_sender.push(action);                 // Jugador 1
          break;
        case SDLK_r:
          action.type_of_movement =
              CHEAT_SPAWN_ARMOR;     // Spawnear armadura completa
          queue_sender.push(action); // Jugador 1
          break;
        case SDLK_t:
          action.type_of_movement = CHEAT_WIN_ROUND; // Ganar ronda
          queue_sender.push(action);                 // Jugador 1
          break;
        case SDLK_v:
          action.type_of_movement = CHEAT_WIN_GAME; // Ganar juego
          queue_sender.push(action);                // Jugador 1
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
        action.type_of_movement = STILL_LEFT;
        queue_sender.push(action);
        break;
      case SDLK_d:
        action.type_of_movement = STILL_RIGHT;
        queue_sender.push(action);
        break;
      case SDLK_LSHIFT:
        action.type_of_movement = STOP_SHOOT;
        queue_sender.push(action); // Detener disparo continuo
        break;
      case SDLK_SPACE:
        action.type_of_movement = STOP_AIM_UP;
        queue_sender.push(action); // Dejar de apuntar arriba
        break;

        // Controles para Jugador 2
      case SDLK_j:
        action.type_of_movement = STILL_LEFT;
        action.player = 2;
        queue_sender.push(action);
        break;
      case SDLK_l:
        action.type_of_movement = STILL_RIGHT;
        action.player = 2;
        queue_sender.push(action);
        break;
      case SDLK_RSHIFT:
        action.type_of_movement = STOP_SHOOT;
        action.player = 2;
        queue_sender.push(action); // Detener disparo continuo
        break;
      case SDLK_m:
        action.type_of_movement = STOP_AIM_UP;
        action.player = 2;
        queue_sender.push(action); // Dejar de apuntar arriba
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
    action.type_of_movement = RIGHT;
    queue_sender.push(action);
  } else if (teclas_presionadas.find(SDLK_a) != teclas_presionadas.end()) {
    action.type_of_movement = LEFT;
    queue_sender.push(action);
  }

  // Mover derecha e izquierda con teclas presionadas para Jugador 2
  if (teclas_presionadas.find(SDLK_l) != teclas_presionadas.end()) {
    action.type_of_movement = RIGHT;
    action.player = 2;
    queue_sender.push(action);
  } else if (teclas_presionadas.find(SDLK_j) != teclas_presionadas.end()) {
    action.type_of_movement = LEFT;
    action.player = 2;
    queue_sender.push(action);
  }

  // Disparo continuo mientras las teclas de disparo estén presionadas
  if (teclas_presionadas.find(SDLK_LSHIFT) != teclas_presionadas.end()) {
    action.type_of_movement = SHOOT;
    queue_sender.push(action);
  }
  if (teclas_presionadas.find(SDLK_RSHIFT) != teclas_presionadas.end()) {
    action.type_of_movement = SHOOT;
    action.player = 2;
    queue_sender.push(action);
  }
}
