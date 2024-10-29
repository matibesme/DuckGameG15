#ifndef GAMERUNNER_H
#define GAMERUNNER_H

#include "Graficos.h"
#include "EventHandler.h"
#include "GameRenderer.h"
#include "Items/ClientDuck.h"
#include "Items/Bullet.h"
#include "common/blocking_queue.h"
#include <list>

class GameRunner {
private:
    Graficos graficos;
    EventHandler handler;
    BlockingQueue<uint8_t>& queue_sender;
    BlockingQueue<GameState>& queue_receiver;

public:
    GameRunner(BlockingQueue<uint8_t>& queue_sender, BlockingQueue<GameState>& queue_receiver);

    void run();
};

#endif // GAMERUNNER_H
