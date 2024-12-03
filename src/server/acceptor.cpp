#include "acceptor.h"

#include <iostream>

Acceptor::Acceptor(const char *port, bool &close)
    : socket_servidor(port), lista_clientes(), close(close),
      cantidad_clientes(UNO), lobby() {}

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

  cantidad_clientes += DOS;
}

void Acceptor::deleteAClient(ThreadCliente &cliente) {
  cliente.delete_client();
}

void Acceptor::reapDead() {
  for (auto it = lista_clientes.begin(); it != lista_clientes.end();) {
    if ((*it).isDead()) {
      (*it).join();
      (*it).stop();
      deleteAClient(*it);
      it = lista_clientes.erase(it);
    } else {
      ++it;
    }
  }
}

void Acceptor::closeSocket() {
  socket_servidor.shutdown(DOS);
  socket_servidor.close();
}

Acceptor::~Acceptor() {
  for (auto it = lista_clientes.begin(); it != lista_clientes.end();) {
    (*it).join();
    deleteAClient(*it);
    it = lista_clientes.erase(it);
  }
}
