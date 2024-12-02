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

void Client::createGame(bool is_double_player, std::string player_1,
                        std::string player_2, std::string game_name,
                        bool &is_available_game) {
  GameAccess game_access;
  game_access.action_type = CREATE_GAME;
  game_access.game_name = game_name;
  game_access.player1_name = player_1;
  game_access.player2_name = player_2;
  game_access.double_player = is_double_player;
  protocolo.sendCreateJoinGameToServer(game_access);
  is_available_game = protocolo.reciveMatchWithSameName();
  // si devuelve true ya existe una partida con el mismo nombre
  // si devuelve false se creo la partida
}

bool Client::checkStartGame() {
  GameAccess game_access;
  game_access.action_type = START_GAME;
  protocolo.sendRequestGameToServer(game_access);
  if (protocolo.reciveGameStarted()) {
    // execute();
    return true;
  }
  return false;
}
void Client::startGame() { execute(); }
void Client::joinGame(std::string game_name, bool is_double_player,
                      std::string player_1, std::string player_2) {
  GameAccess game_access;
  game_access.action_type = JOIN_GAME;
  game_access.game_name = game_name;
  game_access.player1_name = player_1;
  game_access.player2_name = player_2;
  game_access.double_player = is_double_player;
  protocolo.sendCreateJoinGameToServer(game_access);
  execute();
}

std::list<std::string> Client::updateGame() {
  GameAccess game_access;
  game_access.action_type = LISTAR_PARTIDAS;
  protocolo.sendRequestGameToServer(game_access);
  std::list<std::string> list = protocolo.reciveActiveGamesFromServer();

  return list;
}

Client::~Client() {
  queue_sender.close();
  queue_receiver.close();
  receiver.stop();
  sender.stop();
  if (sender.is_alive()) {
    sender.join();
  }
  if (receiver.is_alive()) {
    receiver.join();
  }
}
