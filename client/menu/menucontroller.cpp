#include "menucontroller.h"
#include "menu.h"

#include <QApplication>

MenuController::MenuController(Client &client, int argc, char **argv,
                               QObject *parent)
    : QObject(parent), client(client), argc(argc), argv(argv) {
      this->are_two_players = true;
    }

void MenuController::set_type_game(uint8_t type_game_) {
  this->type_game = type_game_;
}

void MenuController::start_game() {
  QApplication a(argc, argv);
  Menu w;
  w.show();
  connect(&w, &Menu::create, this, &MenuController::create);
  connect(&w, &Menu::start, this, &MenuController::start);
  connect(&w, &Menu::join, this, &MenuController::join);
  connect(&w, &Menu::update_games, this, &MenuController::update_games);
  connect(&w, &Menu::number_players_changed, this, &MenuController::set_number_players);
  a.exec();
}

void MenuController::set_number_players(bool are_two_players) {
    this->are_two_players = are_two_players;
}

void MenuController::create(std::string player_1, std::string player_2) { 
      client.createGame(are_two_players, player_1, player_2); 
}

void MenuController::start() {
  QCoreApplication::quit();
  client.startGame();
}

void MenuController::join(uint8_t id_game, std::string player_1, std::string player_2) {
  QCoreApplication::quit();
  client.joinGame(id_game, are_two_players, player_1, player_2);
}

void MenuController::update_games(Menu &menu) {
  menu.show_update_games(client.updateGame());
}

MenuController::~MenuController() {}
