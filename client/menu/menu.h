#ifndef MENU_H
#define MENU_H
//#include "menucontroller.h"
#include <QMainWindow>
#include <QGraphicsView>

class Menu : public QMainWindow
{
    Q_OBJECT
private:
    QGraphicsView* view;
    QGraphicsScene* main_scene;
    QGraphicsScene* make_game_scene;
    QGraphicsScene* join_game_scene;
    QGraphicsScene* wait_scene;
    //MenuController* menu_controller;

    void initialize();
    void show_main_scene();
    void show_make_game_scene();
    void show_join_game_scene();
    void show_number_players();
    void show_wait_scene();

public:
    Menu(QWidget *parent = nullptr);
    ~Menu();

signals:
    void start();
};
#endif // MENU_H
