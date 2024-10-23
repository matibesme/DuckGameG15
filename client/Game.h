#ifndef GAME_H
#define GAME_H

#include "Duck.h"
#include "Graficos.h"
#include "Background.h"
#include "protocolo_cliente.h"
#include "common/blocking_queue.h"

class Game {

private:
    Graficos graficos;
    Duck duck;
    Background background;
    unsigned int prevTicks;
    SDL2pp::Texture duckTexture;
    ProtocoloCliente& protocol;
    BlockingQueue<uint8_t>& queue_sender;
    BlockingQueue<CommandGameShow>& queue_receiver;
    void dibujar(float pos_x, float pos_y, uint8_t typeOfMove, Renderer& renderer);
    void correrHandlers();

public:

    Game(ProtocoloCliente& protocol, BlockingQueue<uint8_t>& queue_sender, BlockingQueue<CommandGameShow>& queue_receiver);

    void run();
};

#endif // GAME_H
