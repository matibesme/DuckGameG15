#include "menucontroller.h"
#include "menu.h"
#include <QApplication>
#include <string>

MenuController::MenuController(Client &client, Menu &menu, QApplication &a,
                               int argc, char **argv, QObject *parent)
    : QObject(parent), client(client), w(menu), a(a), argc(argc), argv(argv) {
  this->are_two_players = true;
}

void MenuController::start_game() {
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
}

void MenuController::set_number_players(bool are_two_players) {
  this->are_two_players = are_two_players;
}

void MenuController::create(const std::string &player_1,
                            const std::string &player_2,
                            const std::string &game_name) {
  bool is_available_game;
  client.createGame(are_two_players, player_1, player_2, game_name,
                    is_available_game);
  emit show_wait(is_available_game);
}

void MenuController::start() {
  is_new_game = true;
  QCoreApplication::quit();
  // client.startGame();
}

void MenuController::join(const std::string &id_game,
                          const std::string &player_1,
                          const std::string &player_2) {
  this->id_game = id_game;
  this->player_1_name = player_1;
  this->player_2_name = player_2;
  this->is_new_game = false;
  QCoreApplication::quit();
  // client.joinGame(id_game, are_two_players, player_1, player_2);
}

void MenuController::update_games(Menu &menu) {
  menu.show_update_games(client.updateGame());
}

void MenuController::game() {
  if (is_new_game) {
    client.startGame();
  } else {
    client.joinGame(id_game, are_two_players, player_1_name, player_2_name);
  }
}

MenuController::~MenuController() = default;
