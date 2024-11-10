#include "menucontroller.h"

#include <QApplication>

#include "menu.h"

MenuController::MenuController(Client& client, int argc, char** argv, QObject* parent):
        QObject(parent), client(client), argc(argc), argv(argv) {}

void MenuController::set_type_game(uint8_t type_game_) { this->type_game = type_game_; }

void MenuController::start_game() {
    QApplication a(argc, argv);
    Menu w;
    w.show();
    connect(&w, &Menu::start, this, &MenuController::start);
    connect(&w, &Menu::join, this, &MenuController::join);
    a.exec();
    client.execute();
}

void MenuController::set_number_players(uint8_t number_players_) {
    this->number_players = number_players_;
}

// handler de make Game
void MenuController::start() {
    QCoreApplication::quit();
    client.createGame();
    client.startGame();
}

void MenuController::join(uint8_t id_game) {
    QCoreApplication::quit();
    std::cout << (int)id_game;
    client.joinGame(id_game);
}

MenuController::~MenuController() {}
