#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SDL2/SDL.h>
#include <unordered_set>
#include "common/blocking_queue.h"
#include "protocolo_cliente.h"

class EventHandler {
private:
    BlockingQueue<ClientAction>& queue_sender;
    std::unordered_set<SDL_Keycode> teclas_presionadas;

public:
    explicit EventHandler(BlockingQueue<ClientAction>& queue_sender);

    void correrHandlers();
};

#endif // EVENTHANDLER_H
