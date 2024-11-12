#include "client.h"
#define QUEUE_TAMANIO_MAX 1000

Client::Client(const char *host, const char *port)
    : protocolo(host, port, is_socket_close), is_socket_close(false),
      queue_sender(QUEUE_TAMANIO_MAX), queue_receiver(QUEUE_TAMANIO_MAX),
      game(queue_sender, queue_receiver), sender(protocolo, queue_sender),
      receiver(protocolo, queue_receiver) {}

void Client::execute() {
  sender.start();
  receiver.start();
  game.run();
}

void Client::createGame() {
  GameAccess game_access;
  game_access.action_type = CREATE_GAME;
  game_access.game_id = 0;
  game_access.player1_name = "player1";
  game_access.player2_name = "player2";
  game_access.double_player = true;
  protocolo.sendCreateJoinGameToServer(game_access);
}

void Client::startGame() {
  GameAccess game_access;
  game_access.action_type = START_GAME;
  protocolo.sendRequestGameToServer(game_access);
  execute();
}

void Client::joinGame(uint8_t idPartida) {
  GameAccess game_access;
  game_access.action_type = JOIN_GAME;
  game_access.game_id = idPartida;
  game_access.player1_name = "player1";
  game_access.double_player = false;

  protocolo.sendCreateJoinGameToServer(game_access);
  execute();
}

std::list<uint8_t> Client::updateGame() {
  GameAccess game_access;
  game_access.action_type = LISTAR_PARTIDAS;
  protocolo.sendRequestGameToServer(game_access);
  std::list<uint8_t> list = protocolo.reciveActiveGamesFromServer();

  return list;
}

Client::~Client() {
  receiver.stop();
  sender.stop();
  receiver.join();
  sender.join();
}
