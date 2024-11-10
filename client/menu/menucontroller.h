#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H
#include "../client.h"
#include <cstdint>
#include <iostream>
#include <vector>
#include <QObject>

class MenuController: public QObject {
    Q_OBJECT
private:
    uint8_t type_game;
    uint8_t number_players;
    Client& client;

public:
    MenuController(Client& client, QObject *parent = nullptr);
    void set_type_game(uint8_t type_game);
    void set_number_players(uint8_t number_players);
    void start_game();
    ~MenuController();
};

#endif // MENUCONTROLLER_H
