#include "thread_cliente.h"

#include "../common/game_exception.h"

ThreadCliente::ThreadCliente(Socket peer, uint8_t id, LobbyPartidas& lobby):

        dead_connection(),
        queue_sender(std::make_shared<BlockingQueue<GameState>>(50)),
        protocolo(std::move(peer), dead_connection, id),
        id(id),
        lobby(lobby),
        receiver(protocolo, dead_connection, id, lobby),
        sender(protocolo, queue_sender, dead_connection) {}


void ThreadCliente::run() {
    try {
        lobby.addQueueSender(id, queue_sender);
        receiver.start();
        sender.start();

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}


void ThreadCliente::sendAction(const GameState& action) { queue_sender->push(action); }

uint8_t ThreadCliente::getId() { return id; }


bool ThreadCliente::isDead() { return dead_connection; }

void ThreadCliente::setIsDead() { dead_connection = true; }

std::shared_ptr<BlockingQueue<GameState>>& ThreadCliente::getQueueSender() { return queue_sender; }


void ThreadCliente::delete_client() {
    protocolo.closeSocket();
    queue_sender->close();

    receiver.join();
    sender.join();
}

ThreadCliente::~ThreadCliente() {}
