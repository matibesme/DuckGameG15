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
    connect(&w, &Menu::start, this, &MenuController::start);
    a.exec();
    client.execute();
}

void MenuController::set_number_players(uint8_t number_players_){
    this->number_players = number_players_;
}

//handler de make Game
void MenuController::start(){
    QCoreApplication::quit();
    client.createGame();
    client.startGame();
}

MenuController::~MenuController(){
    
}
