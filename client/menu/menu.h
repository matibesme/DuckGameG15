#ifndef MENU_H
#define MENU_H
//#include "menucontroller.h"
#include <QGraphicsView>
#include <QMainWindow>
#include <QMap>
#include <QtWidgets>
#include <iostream>
#include <list>
#include <map>

class Menu: public QMainWindow {
    Q_OBJECT
private:
    QGraphicsView* view;
    QGraphicsScene* main_scene;
    QGraphicsScene* make_game_scene;
    QGraphicsScene* join_game_scene;
    QGraphicsScene* wait_scene;
    QComboBox* game_options;
    QMap<QString, uint8_t> active_games;

    void initialize();
    void show_main_scene();
    void show_make_game_scene();
    void show_join_game_scene();
    void show_wait_scene();

public:
    Menu(QWidget* parent = nullptr);
    void show_update_games(std::list<uint8_t> active_games);
    ~Menu();

signals:
    void create();
    void start();
    void join(uint8_t id_game);
    void update_games(Menu& menu);
};
#endif  // MENU_H
