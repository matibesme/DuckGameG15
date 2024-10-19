#include "thread_cliente.h"

#include "../common_src/game_exception.h"

ThreadCliente::ThreadCliente(Socket peer, BlockingQueue<CommandPickUp>& queue_comandos, uint8_t id):

        dead_connection(),
        queue_comandos(queue_comandos),
        queue_sender(50),
        protocolo(std::move(peer), dead_connection),
        receiver(protocolo, dead_connection, queue_comandos),
        sender(protocolo, queue_sender, dead_connection),
        id(id) {}


void ThreadCliente::run() {
    try {
        receiver.start();
        sender.start();

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}


void ThreadCliente::sendAction(const CommandReward& action) { queue_sender.push(action); }

uint8_t ThreadCliente::getId() { return id; }


bool ThreadCliente::isDead() { return dead_connection; }

void ThreadCliente::setIsDead() { dead_connection = true; }

BlockingQueue<CommandReward>& ThreadCliente::getQueueSender() { return queue_sender; }


void ThreadCliente::delete_client() {
    protocolo.closeSocket();
    queue_sender.close();

    receiver.join();
    sender.join();
}

ThreadCliente::~ThreadCliente() {}
