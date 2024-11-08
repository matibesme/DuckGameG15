#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QGraphicsView>

class Menu : public QMainWindow
{
    Q_OBJECT
private:
    QGraphicsView* view;
    QGraphicsScene* main_scene;

    void initialize_scenes();

public:
    Menu(QWidget *parent = nullptr);
    ~Menu();
};
#endif // MENU_H
