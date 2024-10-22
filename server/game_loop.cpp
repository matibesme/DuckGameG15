#include "game_loop.h"


GameLoop::GameLoop(BlockingQueue<uint8_t>& queue_comandos, bool& end_game,
                   ProtectedQueuesMap& queues_map):
        queue_comandos(queue_comandos),
        end_game(end_game),
        queues_map(queues_map),
        personaje() {}

void GameLoop::run() {
    try {
        while (!end_game) {
           
            processCommands();

        }
    } catch (const ClosedQueue& e) {
        // Queue closed
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}



void GameLoop::processCommands() {
    uint8_t comando;
    while (queue_comandos.try_pop(comando)) {
        if (comando==S_RIGTH){
            personaje.setXPos(MOVEMENT_QUANTITY,true);
            personaje.setTypeOfMove(S_RIGTH);
        } else if (comando==S_LEFT){
            personaje.setXPos(MOVEMENT_QUANTITY,false);
            personaje.setTypeOfMove(S_LEFT);
        } else if (comando==S_JUMP){
            personaje.setTypeOfMove(S_JUMP)
        } else if (comando==S_DOWN){
            personaje.setTypeOfMove(S_DOWN);
        }

        CommandGame command = {S_FULL_GAME_BYTE, 1, 1, {{1, 1, personaje.getXPos(), personaje.getYPos(),
                                                         personaje.getTypeOfMove()}}, 0, ""};
        queues_map.sendMessagesToQueues(command);
    }

}

const float GRAVEDAD = 9.81f;
const float VELOCIDAD_INICIAL = 10.0f; // Velocidad inicial en Y (hacia arriba)
const float TIEMPO_ENTRE_FRAMES = 0.016f; // Simulación a 60 FPS (1/60 = 0.016 segundos)


/*void GameLoop::saltar() {
    int tope = personaje.getYPos() + 5;
    while (personaje.getYPos() != tope) {
    if(personaje  tope ) {

    }

    }

}*/

/* if (isJumping && !tocoTecho) {
        colSprite = JUMP_SPRITE_INDEX;
        isOnFloor = false;
        positionY += jumpVelocity * frameDelta * JUMP_VELOCITY_SCALE;
    } else {
        isJumping = false;
        positionY -= jumpVelocity * frameDelta * JUMP_VELOCITY_SCALE;
        if (positionY >= initialY) {
            positionY = initialY;
            tocoTecho = false;
        }
    }*/

GameLoop::~GameLoop() {}
