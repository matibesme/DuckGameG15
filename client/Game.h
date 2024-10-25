#ifndef GAME_H
#define GAME_H

#include "Duck.h"
#include "Bullet.h"
#include "Graficos.h"
#include "Background.h"
#include "protocolo_cliente.h"
#include "common/blocking_queue.h"

class Game {

private:
    Graficos graficos;
    Duck duck;
    Background background;
    BlockingQueue<uint8_t>& queue_sender;
    BlockingQueue<CommandGameShow>& queue_receiver;
    void dibujar(Renderer& renderer , std::list<Bullet>& bullets);
    void correrHandlers();

public:
    Game(BlockingQueue<uint8_t>& queue_sender, BlockingQueue<CommandGameShow>& queue_receiver);

    void run();
};

#endif // GAME_H
