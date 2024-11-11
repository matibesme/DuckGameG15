#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H
#include <QObject>
#include <cstdint>
#include <iostream>
#include <vector>

#include "../client.h"

#include "menu.h"

class MenuController : public QObject {
  Q_OBJECT
private:
  uint8_t type_game;
  uint8_t number_players;
  Client &client;
  int argc;
  char **argv;

public:
  MenuController(Client &client, int argc, char **argv,
                 QObject *parent = nullptr);
  void set_type_game(uint8_t type_game);
  void set_number_players(uint8_t number_players);
  void start_game();
  ~MenuController();

public slots:
  void create();
  void start();
  void join(uint8_t id_game);
  void update_games(Menu &menu);
};

#endif // MENUCONTROLLER_H
