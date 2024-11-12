#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H
#include "../client.h"
#include "menu.h"
#include <QObject>
#include <cstdint>
#include <iostream>
#include <vector>

class MenuController : public QObject {
  Q_OBJECT
private:
  uint8_t type_game;
  Client &client;
  int argc;
  char **argv;
  std::string player_1_name;
  std::string player_2_name;
  bool are_two_players;

public:
  MenuController(Client &client, int argc, char **argv,
                 QObject *parent = nullptr);
  void set_type_game(uint8_t type_game);
  void start_game();
  ~MenuController();

public slots:
  void start();
  void create(std::string player_1, std::string player_2,  std::string game_name);
  void join(std::string id_game, std::string player_1, std::string player_2);
  void update_games(Menu &menu);
  void set_number_players(bool are_two_players);

signals:
  void show_wait(bool is_available_name);
};

#endif // MENUCONTROLLER_H
