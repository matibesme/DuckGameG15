#include "game_loop.h"


GameLoop::GameLoop(BlockingQueue<uint8_t>& queue_comandos, bool& end_game,
                   ProtectedQueuesMap& queues_map):
        queue_comandos(queue_comandos),
        end_game(end_game),
        queues_map(queues_map),
        personaje(),
        lista_personajes()
        {}

void GameLoop::run() {
    try {
        while (!end_game) {
            uint8_t comando;
            while (queue_comandos.try_pop(comando)) {
                checkCommand(comando);
            }
            paraCadaPatoAction();
            sendCompleteScene();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

    } catch (const ClosedQueue& e) {
        // Queue closed
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void GameLoop::checkCommand(uint8_t comando) {
    std::cout << "Comando recibido: " << (int)comando << std::endl;
    if (comando==S_RIGTH){
        personaje.setXPos(MOVEMENT_QUANTITY_X);
        personaje.setTypeOfMoveSprite(S_RIGTH);
    } else if (comando==S_LEFT){
        personaje.setXPos(-MOVEMENT_QUANTITY_X);
        personaje.setTypeOfMoveSprite(S_LEFT);
    } else if (comando==S_JUMP && !personaje.estaSaltando()){
        personaje.setEnSalto(true);
    } else if (comando==S_DOWN){
        personaje.setTypeOfMoveSprite(S_DOWN);
    }else if (comando==S_STILL && !personaje.estaSaltando()){
        personaje.setTypeOfMoveSprite(S_STILL);
    }

    sendCompleteScene();
}

void GameLoop::sendCompleteScene(){
    CommandGame command = {S_FULL_GAME_BYTE, 1, 1, {{1, 1, personaje.getXPos(), personaje.getYPos(),
                                                     personaje.getTypeOfMoveSprite()}}, 0, ""};
    queues_map.sendMessagesToQueues(command);

}

void GameLoop::paraCadaPatoAction() {
    float gravedad = 0.5; // Valor de gravedad, ajusta según la escala de tu juego.
    for (auto& personaje_i : lista_personajes) {
        if (personaje_i.estaSaltando()) {
            personaje_i.setYPos(personaje_i.getYPos() + personaje_i.getVelocidadY()); // Actualiza la posición vertical
            personaje_i.setVelocidadY(personaje_i.getVelocidadY() - gravedad); // Aplica la gravedad

            if (personaje_i.getYPos() <= 0) { // Si el personaje toca el suelo (Y = 0)
                personaje_i.setYPos(0); // Restablece la posición en el suelo
                personaje_i.setEnSalto(false); // El personaje ha aterrizado
                personaje_i.setVelocidadY(20); // Reinicia la velocidad del salto para la próxima vez
            }
        }
    }
}

GameLoop::~GameLoop() {}
