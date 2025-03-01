#ifndef MENU_H
#define MENU_H
// #include "menucontroller.h"
#include <QGraphicsView>
#include <QMainWindow>
#include <QMap>
#include <QtWidgets>
#include <iostream>
#include <list>
#include <map>
#include <string>
class Menu : public QMainWindow {
  Q_OBJECT

private:
  QGraphicsView *view;
  QGraphicsScene *main_scene;
  QGraphicsScene *make_game_scene;
  QGraphicsScene *join_game_scene;
  QGraphicsScene *wait_scene;
  QComboBox *game_options;
  QMap<QString, std::string> active_games;

  void initialize();
  void show_main_scene();
  void show_make_game_scene();
  void show_join_game_scene();
  void show_wait_scene();

public:
  explicit Menu(QWidget *parent = nullptr);
  void show_update_games(std::list<std::string> active_games);
  ~Menu();

public slots:
  void show_wait(bool is_available_name);

signals:
  void start();
  void create(std::string player_1, std::string player_2,
              std::string game_name);
  void join(std::string id_game, std::string player_1, std::string player_2);
  void update_games(Menu &menu);
  void number_players_changed(bool are_two_players);
};
#endif // MENU_H
