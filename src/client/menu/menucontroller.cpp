#include "menucontroller.h"
#include "menu.h"
#include <QApplication>
#include <string>

MenuController::MenuController(Client &client, Menu &menu, QApplication &a,
                               int argc, char **argv, QObject *parent)
    : QObject(parent), client(client), w(menu), a(a), argc(argc), argv(argv) {
  this->are_two_players = true;
  this->was_game_initialized = false;
  this->is_new_game = false;
}

void MenuController::start_game() try {
  // QApplication a(argc, argv);
  connect(&w, &Menu::create, this, &MenuController::create);
  connect(&w, &Menu::start, this, &MenuController::start);
  connect(&w, &Menu::join, this, &MenuController::join);
  connect(&w, &Menu::update_games, this, &MenuController::update_games);
  connect(&w, &Menu::number_players_changed, this,
          &MenuController::set_number_players);
  connect(this, &MenuController::show_wait, &w, &Menu::show_wait);
  w.show();
  a.exec();
} catch (const SocketClose &e) {
  w.close();
  QCoreApplication::quit();
}

void MenuController::set_number_players(bool are_two_players) {
  this->are_two_players = are_two_players;
}

void MenuController::create(const std::string &player_1,
                            const std::string &player_2,
                            const std::string &game_name) try {
  bool is_available_game;
  client.createGame(are_two_players, player_1, player_2, game_name,
                    is_available_game);
  emit show_wait(is_available_game);
} catch (const SocketClose &e) {
  w.close();
  QCoreApplication::quit();
}

void MenuController::start() try {
  is_new_game = true;
  this->was_game_initialized = true;
  if (client.checkStartGame()) {
    w.close();
    QCoreApplication::quit();
  }
} catch (const SocketClose &e) {
  w.close();
  QCoreApplication::quit();
}

void MenuController::join(const std::string &id_game,
                          const std::string &player_1,
                          const std::string &player_2) {
  this->id_game = id_game;
  this->player_1_name = player_1;
  this->player_2_name = player_2;
  this->is_new_game = false;
  this->was_game_initialized = true;
  QCoreApplication::quit();
}

void MenuController::update_games(Menu &menu) try {
  menu.show_update_games(client.updateGame());
} catch (const SocketClose &e) {
  w.close();
  QCoreApplication::quit();
}

void MenuController::game() {
  if (was_game_initialized) {
    if (is_new_game) {
      client.startGame();
    } else {
      client.joinGame(id_game, are_two_players, player_1_name, player_2_name);
    }
  }
}

MenuController::~MenuController() = default;
