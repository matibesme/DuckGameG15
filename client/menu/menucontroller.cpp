#include "menucontroller.h"
#include "menu.h"

#include <QApplication>

MenuController::MenuController(Client& client, int argc, char** argv, QObject *parent) : QObject(parent), client(client), argc(argc), argv(argv){

}

void MenuController::set_type_game(uint8_t type_game){
    this->type_game = type_game;
}

void MenuController::start_game(){
    QApplication a(argc, argv);
    Menu w;
    w.show();
    connect(&w, &Menu::start, this, &MenuController::start);
    a.exec();
    client.execute();
}

void MenuController::set_number_players(uint8_t number_players){
    this->number_players = number_players;
}

void MenuController::start(){
    QCoreApplication::quit();
}

MenuController::~MenuController(){
    
}
