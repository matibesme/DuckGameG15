#ifndef GAMERUNNER_H
#define GAMERUNNER_H

#include "Graficos.h"
#include "EventHandler.h"
#include "GameRenderer.h"
#include "Items/Duck.h"
#include "Items/Bullet.h"
#include "common/blocking_queue.h"
#include <list>

class GameRunner {
private:
    Graficos graficos;
    GameRenderer gameRenderer;
    EventHandler handler;
    BlockingQueue<uint8_t>& queue_sender;
    BlockingQueue<CommandGameShow>& queue_receiver;
    void actualizarElementos(const CommandGameShow &command, std::list<Duck> &ducks, std::list<Bullet> &bullets);

public:
    GameRunner(BlockingQueue<uint8_t>& queue_sender, BlockingQueue<CommandGameShow>& queue_receiver);

    void run();
};

#endif // GAMERUNNER_H
