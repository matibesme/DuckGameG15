#include "menu.h"

#include <QtWidgets>

Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
{
    initialize_scenes();
}

void Menu::initialize_scenes(){
    main_scene = new QGraphicsScene(this);
    view = new QGraphicsView(main_scene, this);

    view->setGeometry(0, 0, 800, 600);
    main_scene->setSceneRect(0, 0, 800, 600);
    QPixmap initial_background("../../data/menu/Background.jpg");
    QPushButton* make_game = new QPushButton("Make game");
    make_game->setGeometry(325, 400, 150, 45);
    make_game->setStyleSheet(
                "QPushButton {"
                "   background-color: #404040;"
                "   color: white;"
                "   border-radius: 1px;"
                "   padding: 10px"
                "}"
                "QPushButton:hover {"
                "   background-color: #ffffff;"
                "    color: black;"
                "   border-radius: 1px;"
                "}"
                "QPushButton:pressed {"
                "   background-color: #c7c7c7;"
                "   color: black;"
                "}"
                );
    QPushButton* join_game = new QPushButton("Join game");
    join_game->setGeometry(325, 450, 150, 45);
    join_game->setStyleSheet(
                "QPushButton {"
                "   background-color: #404040;"
                "   color: white;"
                "   border-radius: 5px;"
                "padding: 10px"
                "}"
                "QPushButton:hover {"
                "   background-color: #ffffff;"
                "    color: black;"
                "   border-radius: 1px;"
                "}"
                "QPushButton:pressed {"
                "   background-color: #c7c7c7;"
                "   color: black;"
                "}"
                );
    QPushButton* quit = new QPushButton("Quit");
    quit->setGeometry(350, 500, 100, 45);
    quit->setStyleSheet(
                "QPushButton {"
                "   background-color: #404040;"
                "   color: white;"
                "   border-radius: 5px;"
                "padding: 10px"
                "}"
                "QPushButton:hover {"
                "   background-color: #ffffff;"
                "    color: black;"
                "   border-radius: 1px;"
                "}"
                "QPushButton:pressed {"
                "   background-color: #c7c7c7;"
                "   color: black;"
                "}"
                );
    main_scene->setBackgroundBrush(initial_background);
    main_scene->addWidget(make_game);
    main_scene->addWidget(join_game);
    main_scene->addWidget(quit);
    view->setScene(main_scene);
    view->show();
}

Menu::~Menu()
{
}

