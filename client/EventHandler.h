#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <unordered_set>

#include <SDL2/SDL.h>

#include "common/blocking_queue.h"

#include "protocolo_cliente.h"

class EventHandler {
private:
    BlockingQueue<uint8_t>& queue_sender;
    std::unordered_set<SDL_Keycode> teclas_presionadas;

public:
    explicit EventHandler(BlockingQueue<uint8_t>& queue_sender);

    void correrHandlers();
};

#endif  // EVENTHANDLER_H
