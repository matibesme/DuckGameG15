#include "acceptor.h"

#include <iostream>


Acceptor::Acceptor(const char* port, ProtectedQueuesMap& map_queues_sender,
                   BlockingQueue<uint8_t>& queue_comandos, bool& close):
        socket_servidor(port),
        map_queues_sender(map_queues_sender),
        lista_clientes(),
        queue_comandos(queue_comandos),
        close(close),
        cantidad_clientes(0) {}


void Acceptor::accept_new_client() {
    Socket peer = socket_servidor.accept();

    lista_clientes.emplace_back(std::move(peer), queue_comandos, cantidad_clientes);
    ThreadCliente& cliente = lista_clientes.back();
    cliente.start();
    reapDead();
    
    map_queues_sender.addClient(cantidad_clientes, cliente.getQueueSender());//
    cantidad_clientes++;
}


void Acceptor::run() {

    while (!close) {
        try {

            accept_new_client();
        } catch (const std::exception& e) {
            if (!close) {
                std::cerr << e.what() << std::endl;
            }
            // sino cerro el socket por el close de forma esperada
        }
    }
}

void Acceptor::deleteAClient(ThreadCliente& cliente) {
    cliente.delete_client();
    map_queues_sender.removeQueue(cliente.getId());
}


void Acceptor::reapDead() {

    for (auto it = lista_clientes.begin(); it != lista_clientes.end();) {
        if (it->isDead()) {
            it->join();
            deleteAClient(*it);
            lista_clientes.erase(it);
        } else {
            ++it;
        }
    }
}


void Acceptor::closeSocket() {
    socket_servidor.shutdown(2);
    socket_servidor.close();
}

Acceptor::~Acceptor() {
    for (auto& it: lista_clientes) {
        it.join();
        deleteAClient(it);
    }
    lista_clientes.clear();
}
