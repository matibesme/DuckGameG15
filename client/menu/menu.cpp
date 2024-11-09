#include "menu.h"
#include "menucontroller.h"

#include <QtWidgets>
#include <QHBoxLayout>
#include <QVBoxLayout>

Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
{
    menu_controller = new MenuController();
    initialize();
    show_main_scene();
}

void Menu::initialize(){
    main_scene = new QGraphicsScene(this);
    make_game_scene = new QGraphicsScene(this);
    join_game_scene = new QGraphicsScene(this);
    wait_scene = new QGraphicsScene(this);
    view = new QGraphicsView(main_scene, this);

    this->setGeometry(0, 0, 800, 600);
    view->setGeometry(0, 0, 800, 600);
    main_scene->setSceneRect(0, 0, 800, 600);
    make_game_scene->setSceneRect(0, 0, 800, 600);
    join_game_scene->setSceneRect(0, 0, 800, 600);
    wait_scene->setSceneRect(0, 0, 800, 600);
}

void Menu::show_main_scene(){

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
    connect(make_game, &QPushButton::pressed, this, &Menu::show_make_game_scene);
    connect(make_game, &QPushButton::pressed, [this, make_game](){
        menu_controller->set_type_game(0);
    });
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
    connect(join_game, &QPushButton::pressed, this, &Menu::show_join_game_scene);
    connect(join_game, &QPushButton::pressed, [this, make_game](){
        menu_controller->set_type_game(1);
    });
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

void Menu::show_make_game_scene(){
    QPixmap initial_background("../../data/menu/Background.jpg");

    //Columna 1
    QWidget *widget_players = new QWidget;
    QVBoxLayout *layout_players = new QVBoxLayout(widget_players);

    QWidget *widget_choose_players = new QWidget;
    QHBoxLayout *layout_choose_players = new QHBoxLayout(widget_choose_players);

    QWidget *widget_name_players = new QWidget;
    QVBoxLayout *layout_name_players = new QVBoxLayout(widget_name_players);

    QPushButton* single_player = new QPushButton("Single player");
    QPushButton* two_players = new QPushButton("Two players");
    layout_choose_players->addWidget(single_player);
    layout_choose_players->addWidget(two_players);

    layout_name_players->addWidget(new QLabel("Enter your name, player 1"));
    QLineEdit* name_player_1 = new QLineEdit();
    layout_name_players->addWidget(name_player_1);

    QLabel* label_player_2 = new QLabel("Enter your name, player 2");
    layout_name_players->addWidget(label_player_2);
    QLineEdit* name_player_2 = new QLineEdit();
    layout_name_players->addWidget(name_player_2);

    QSpacerItem* spacer = new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout_name_players->addItem(spacer);

    connect(single_player, &QPushButton::pressed, [=]() {
        name_player_2->setVisible(false);
        label_player_2->setVisible(false);
    });
    connect(two_players, &QPushButton::pressed, [=]() {
        name_player_2->setVisible(true);
        label_player_2->setVisible(true);
    });

    layout_players->addWidget(widget_choose_players);
    layout_players->addWidget(widget_name_players);

    widget_players->setGeometry(150, 200, 200, 100);

    //Columna 2
    QWidget *widget_game = new QWidget;
    QVBoxLayout *layout_game = new QVBoxLayout(widget_game);

    /*layout_game->addWidget(new QLabel("IP Address"));
    QLineEdit* address = new QLineEdit();
    layout_game->addWidget(address);
    layout_game->addWidget(new QLabel("Port"));
    QLineEdit* port = new QLineEdit();
    layout_game->addWidget(port);*/
    QPushButton* make_game_button = new QPushButton("Make game");
    layout_game->addWidget(make_game_button);
    connect(make_game_button, &QPushButton::pressed, this, &Menu::show_wait_scene);
    QPushButton* back_button = new QPushButton("Back");
    layout_game->addWidget(back_button);
    connect(back_button, &QPushButton::pressed, this, &Menu::show_main_scene);
    widget_game->setGeometry(400, 200, 200, 100);

    make_game_scene->addWidget(widget_players);
    make_game_scene->addWidget(widget_game);
    make_game_scene->setBackgroundBrush(initial_background);
    view->setScene(make_game_scene);
    view->show();
}

void Menu::show_join_game_scene(){
    QPixmap initial_background("../../data/menu/Background.jpg");

    //Columna 1
    QWidget *widget_players = new QWidget;
    QVBoxLayout *layout_players = new QVBoxLayout(widget_players);

    QWidget *widget_choose_players = new QWidget;
    QHBoxLayout *layout_choose_players = new QHBoxLayout(widget_choose_players);

    QWidget *widget_name_players = new QWidget;
    QVBoxLayout *layout_name_players = new QVBoxLayout(widget_name_players);

    QPushButton* single_player = new QPushButton("Single player");
    QPushButton* two_players = new QPushButton("Two players");
    layout_choose_players->addWidget(single_player);
    layout_choose_players->addWidget(two_players);

    layout_name_players->addWidget(new QLabel("Enter your name, player 1"));
    QLineEdit* name_player_1 = new QLineEdit();
    layout_name_players->addWidget(name_player_1);

    QLabel* label_player_2 = new QLabel("Enter your name, player 2");
    layout_name_players->addWidget(label_player_2);
    QLineEdit* name_player_2 = new QLineEdit();
    layout_name_players->addWidget(name_player_2);

    QSpacerItem* spacer = new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout_name_players->addItem(spacer);

    connect(single_player, &QPushButton::pressed, [=]() {
        name_player_2->setVisible(false);
        label_player_2->setVisible(false);
    });
    connect(two_players, &QPushButton::pressed, [=]() {
        name_player_2->setVisible(true);
        label_player_2->setVisible(true);
    });

    layout_players->addWidget(widget_choose_players);
    layout_players->addWidget(widget_name_players);

    widget_players->setGeometry(150, 200, 200, 100);

    //Columna 2
    QWidget *widget_games = new QWidget;
    QVBoxLayout *layout_games = new QVBoxLayout(widget_games);


    QComboBox *game_options = new QComboBox();
    game_options->addItem("Partida1");
    game_options->addItem("Partida2");
    game_options->addItem("Partida3");
    layout_games->addWidget(new QLabel("Select a game:"));
    layout_games->addWidget(game_options);
    QPushButton* join_game_button = new QPushButton("Join game");
    layout_games->addWidget(join_game_button);
    connect(join_game_button, &QPushButton::pressed, this, &Menu::show_wait_scene);
    QPushButton* back_button = new QPushButton("Back");
    connect(back_button, &QPushButton::pressed, this, &Menu::show_main_scene);
    layout_games->addWidget(back_button);

    widget_games->setGeometry(400, 200, 200, 100);

    join_game_scene->addWidget(widget_games);
    join_game_scene->addWidget(widget_players);
    join_game_scene->setBackgroundBrush(initial_background);
    view->setScene(join_game_scene);
    view->show();

}

void Menu::show_number_players(){

}

void Menu::show_wait_scene(){
    QPixmap initial_background("../../data/menu/Background.jpg");
    QWidget *widget_wait = new QWidget;
    QVBoxLayout *layout_wait = new QVBoxLayout(widget_wait);
    layout_wait->addWidget(new QLabel("Waiting for the game to start"));

    //Esto es solo para el cliente que crea el juego.
    QPushButton* start_game = new QPushButton("Start game");
    layout_wait->addWidget(start_game);

    widget_wait->setGeometry(300, 250, 100, 100);
    wait_scene->addWidget(widget_wait);
    wait_scene->setBackgroundBrush(initial_background);
    view->setScene(wait_scene);
    view->show();
}
Menu::~Menu()
{
  delete menu_controller;
}

