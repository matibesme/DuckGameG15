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
    connect(&w, &Menu::create, this, &MenuController::create);
    connect(&w, &Menu::start, this, &MenuController::start);
    connect(&w, &Menu::join, this, &MenuController::join);
    connect(&w, &Menu::update_games, this, &MenuController::update_games);
    a.exec();
    client.execute();
}

void MenuController::set_number_players(uint8_t number_players_) {
    this->number_players = number_players_;
}

void MenuController::create() { client.createGame(); }

// handler de make Game
void MenuController::start() {
    QCoreApplication::quit();
    client.createGame();
    client.startGame();
}

void MenuController::join(uint8_t id_game) {
    QCoreApplication::quit();
    // Código para probar.
    // std::cout << "El id game es: " << (int) id_game << std::endl;
    client.joinGame(id_game);
}

void MenuController::update_games(Menu& menu) {
    // Codigo para probar.
    /*std::list<uint8_t> lista_prueba;
    lista_prueba.emplace_back(45);
    lista_prueba.emplace_back(23);
    lista_prueba.emplace_back(12);
    lista_prueba.emplace_back(4);
    lista_prueba.emplace_back(110);
    menu.show_update_games(lista_prueba);*/
    menu.show_update_games(client.updateGame(0));
}

MenuController::~MenuController() {}
