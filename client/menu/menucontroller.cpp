#include "menucontroller.h"
#include "menu.h"

#include <QApplication>

MenuController::MenuController(Client& client, int argc, char** argv, QObject *parent) : QObject(parent), client(client), argc(argc), argv(argv){

}

void MenuController::set_type_game(uint8_t type_game_){
    this->type_game = type_game_;
}

void MenuController::start_game(){
    QApplication a(argc, argv);
    Menu w;
    w.show();
    connect(&w, &Menu::create, this, &MenuController::create);
    connect(&w, &Menu::start, this, &MenuController::start);
    connect(&w, &Menu::join, this, &MenuController::join);
    connect(&w, &Menu::update_games, this, &MenuController::update_games);
    a.exec();

}

void MenuController::set_number_players(uint8_t number_players_){
    this->number_players = number_players_;
}

void MenuController::create(){
    client.createGame();
}

void MenuController::start(){
    QCoreApplication::quit();
    client.startGame();
}

void MenuController::join(uint8_t id_game){
    QCoreApplication::quit();
    client.joinGame(id_game);
}

void MenuController::update_games(Menu& menu){
    menu.show_update_games(client.updateGame());
}

MenuController::~MenuController(){
    
}
