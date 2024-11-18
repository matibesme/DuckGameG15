#include "acceptor.h"

#include <iostream>

Acceptor::Acceptor(const char *port, bool &close)
    : socket_servidor(port), lista_clientes(), close(close),
      cantidad_clientes(1), lobby() {}

void Acceptor::run() {

  while (!close) {
    try {
      accept_new_client();
    } catch (const std::exception &e) {
      if (!close) {
        std::cout << "Error en el accept" << std::endl;
        std::cerr << e.what() << std::endl;
      }
      // sino cerro el socket por el close de forma esperada
    }
  }
}

void Acceptor::accept_new_client() {
  Socket peer = socket_servidor.accept();

  lista_clientes.emplace_back(std::move(peer), cantidad_clientes, lobby);
  ThreadCliente &cliente = lista_clientes.back();
  cliente.start();
  reapDead();
  lobby.removeGame();

  cantidad_clientes += 2;
}

void Acceptor::deleteAClient(ThreadCliente &cliente) {
  cliente.delete_client();
  lobby.removeQueue(cliente.getId());
}

void Acceptor::reapDead() {
  for (auto it = lista_clientes.begin(); it != lista_clientes.end();) {
    if ((*it).isDead()) { // Nota: Si `it` es un puntero, asegúrate de usar
                          // `(*it)`
      (*it).join();
      deleteAClient(*it);
      it = lista_clientes.erase(
          it); // Actualiza el iterador con el valor devuelto por erase
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
  for (auto &it : lista_clientes) {
    it.join();
    deleteAClient(it);
  }
  lista_clientes.clear();
  lobby.~LobbyPartidas();
}
