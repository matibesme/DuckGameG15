#include "menucontroller.h"

MenuController::MenuController(Client& client, QObject *parent) : QObject(parent), client(client){

}

void MenuController::set_type_game(uint8_t type_game){
    this->type_game = type_game;
}

void MenuController::start_game(){
    client.execute();
}

void MenuController::set_number_players(uint8_t number_players){
    this->number_players = number_players;
}

MenuController::~MenuController(){
    
}
