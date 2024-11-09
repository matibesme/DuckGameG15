#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H
#include <cstdint>
#include <iostream>
#include <vector>

class MenuController{
private:
    uint8_t type_game;
    uint8_t number_players;

public:
    MenuController();
    void set_type_game(uint8_t type_game);
    void set_number_players(uint8_t number_players);
    void start_game();
};

#endif // MENUCONTROLLER_H
