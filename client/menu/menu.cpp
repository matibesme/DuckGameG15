#include "menu.h"
// #include "menucontroller.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtWidgets>
#include <iostream>

Menu::Menu(QWidget *parent) : QMainWindow(parent) {
  // menu_controller = new MenuController();
  initialize();
  show_main_scene();
}

void Menu::initialize() {
  main_scene = new QGraphicsScene(this);
  make_game_scene = new QGraphicsScene(this);
  join_game_scene = new QGraphicsScene(this);
  wait_scene = new QGraphicsScene(this);
  view = new QGraphicsView(main_scene, this);
  game_options = new QComboBox(this);
  game_options->setVisible(false);

  this->setGeometry(0, 0, 800, 600);
  view->setGeometry(0, 0, 800, 600);
  main_scene->setSceneRect(0, 0, 800, 600);
  make_game_scene->setSceneRect(0, 0, 800, 600);
  join_game_scene->setSceneRect(0, 0, 800, 600);
  wait_scene->setSceneRect(0, 0, 800, 600);
}

void Menu::show_main_scene() {

  std::string path =
      std::string(DATA_PATH) + std::string("/menu/Background.jpg");
  QString path_image = QString::fromStdString(path);
  QPixmap initial_background(path_image);
  QPushButton *make_game = new QPushButton("Make game");
  make_game->setGeometry(325, 400, 150, 45);
  make_game->setStyleSheet("QPushButton {"
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
                           "}");
  connect(make_game, &QPushButton::clicked, this, &Menu::show_make_game_scene);
  /*connect(make_game, &QPushButton::pressed, [this, make_game](){
      menu_controller->set_type_game(0);
  });*/
  QPushButton *join_game = new QPushButton("Join game");
  join_game->setGeometry(325, 450, 150, 45);
  join_game->setStyleSheet("QPushButton {"
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
                           "}");
  connect(join_game, &QPushButton::clicked, this, &Menu::show_join_game_scene);
  /*connect(join_game, &QPushButton::pressed, [this, make_game](){
      menu_controller->set_type_game(1);
  });*/
  QPushButton *quit = new QPushButton("Quit");
  quit->setGeometry(350, 500, 100, 45);
  quit->setStyleSheet("QPushButton {"
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
                      "}");
  main_scene->setBackgroundBrush(initial_background);
  main_scene->addWidget(make_game);
  main_scene->addWidget(join_game);
  main_scene->addWidget(quit);
  view->setScene(main_scene);
  view->show();
}

void Menu::show_make_game_scene() {
  std::string path =
      std::string(DATA_PATH) + std::string("/menu/Background.jpg");
  QString path_image = QString::fromStdString(path);
  QPixmap initial_background(path_image);

  // Columna 1
  QWidget *widget_players = new QWidget;
  QVBoxLayout *layout_players = new QVBoxLayout(widget_players);

  QWidget *widget_choose_players = new QWidget;
  QHBoxLayout *layout_choose_players = new QHBoxLayout(widget_choose_players);

  QWidget *widget_name_players = new QWidget;
  QVBoxLayout *layout_name_players = new QVBoxLayout(widget_name_players);

  QPushButton *single_player = new QPushButton("Single player");
  QPushButton *two_players = new QPushButton("Two players");
  layout_choose_players->addWidget(single_player);
  layout_choose_players->addWidget(two_players);

  layout_name_players->addWidget(new QLabel("Enter your name, player 1"));
  QLineEdit *name_player_1 = new QLineEdit();
  layout_name_players->addWidget(name_player_1);
  QLabel *label_player_1_error = new QLabel("Error, enter a name");
  layout_name_players->addWidget(label_player_1_error);
  label_player_1_error->setVisible(false);
  label_player_1_error->setStyleSheet("color: red");

  QLabel *label_player_2 = new QLabel("Enter your name, player 2");
  layout_name_players->addWidget(label_player_2);
  QLineEdit *name_player_2 = new QLineEdit();
  layout_name_players->addWidget(name_player_2);
  QLabel *label_player_2_error = new QLabel("Error, enter a name");
  layout_name_players->addWidget(label_player_2_error);
  label_player_2_error->setVisible(false);
  label_player_2_error->setStyleSheet("color: red");

  QSpacerItem *spacer =
      new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
  layout_name_players->addItem(spacer);

  connect(single_player, &QPushButton::clicked, [this, name_player_2, label_player_2, label_player_1_error, label_player_2_error]() {
    name_player_2->setVisible(false);
    label_player_2->setVisible(false);
    label_player_1_error->setVisible(false);
    label_player_2_error->setVisible(false);
    emit number_players_changed(false);
  });
  connect(two_players, &QPushButton::clicked, [this, name_player_2, label_player_2, label_player_1_error, label_player_2_error]() {
    name_player_2->setVisible(true);
    label_player_2->setVisible(true);
    label_player_1_error->setVisible(false);
    label_player_2_error->setVisible(false);
    emit number_players_changed(true);
  });

  layout_players->addWidget(widget_choose_players);
  layout_players->addWidget(widget_name_players);

  widget_players->setGeometry(150, 200, 200, 100);

  // Columna 2
  QWidget *widget_game = new QWidget;
  QVBoxLayout *layout_game = new QVBoxLayout(widget_game);

  layout_game->addWidget(new QLabel("Game name"));
  QLineEdit* game_name = new QLineEdit();
  layout_game->addWidget(game_name);
  QLabel *label_game_name_error = new QLabel("Error, enter a name");
  layout_game->addWidget(label_game_name_error);
  label_game_name_error->setVisible(false);
  label_game_name_error->setStyleSheet("color: red");

  QPushButton *make_game_button = new QPushButton("Make game");
  layout_game->addWidget(make_game_button);
  connect(make_game_button, &QPushButton::clicked, this, [this, name_player_1, name_player_2, game_name, label_player_1_error, label_player_2_error, label_game_name_error]() { 
    bool are_fields_empties = false;

    if(name_player_1->text().isEmpty()){
      label_player_1_error->setVisible(true);
      are_fields_empties = true;
    }else{
      label_player_1_error->setVisible(false);
    }

    if(name_player_2->text().isEmpty() && name_player_2->isVisible()){
      label_player_2_error->setVisible(true);
      are_fields_empties = true;
    }else{
      label_player_2_error->setVisible(false);
    }

    if(game_name->text().isEmpty()){
      label_game_name_error->setVisible(true);
      are_fields_empties = true;
    }else{
      label_game_name_error->setVisible(false);
    }

    if(!are_fields_empties){
      std::string player_1 = std::string(name_player_1->text().toStdString());
      std::string player_2 = std::string(name_player_2->text().toStdString());
      std::string game = std::string(game_name->text().toStdString());
      emit create(player_1, player_2, game); 
    }
  });

  QPushButton *back_button = new QPushButton("Back");
  layout_game->addWidget(back_button);
  connect(back_button, &QPushButton::clicked, this, &Menu::show_main_scene);
  widget_game->setGeometry(400, 200, 200, 100);

  make_game_scene->addWidget(widget_players);
  make_game_scene->addWidget(widget_game);
  make_game_scene->setBackgroundBrush(initial_background);
  view->setScene(make_game_scene);
  view->show();
}

void Menu::show_join_game_scene() {
  std::string path =
      std::string(DATA_PATH) + std::string("/menu/Background.jpg");
  QString path_image = QString::fromStdString(path);
  QPixmap initial_background(path_image);

  // Columna 1
  QWidget *widget_players = new QWidget;
  QVBoxLayout *layout_players = new QVBoxLayout(widget_players);

  QWidget *widget_choose_players = new QWidget;
  QHBoxLayout *layout_choose_players = new QHBoxLayout(widget_choose_players);

  QWidget *widget_name_players = new QWidget;
  QVBoxLayout *layout_name_players = new QVBoxLayout(widget_name_players);

  QPushButton *single_player = new QPushButton("Single player");
  QPushButton *two_players = new QPushButton("Two players");
  layout_choose_players->addWidget(single_player);
  layout_choose_players->addWidget(two_players);

  layout_name_players->addWidget(new QLabel("Enter your name, player 1"));
  QLineEdit *name_player_1 = new QLineEdit();
  layout_name_players->addWidget(name_player_1);
  QLabel *label_player_1_error = new QLabel("Error, enter a name");
  layout_name_players->addWidget(label_player_1_error);
  label_player_1_error->setVisible(false);
  label_player_1_error->setStyleSheet("color: red");

  QLabel *label_player_2 = new QLabel("Enter your name, player 2");
  layout_name_players->addWidget(label_player_2);
  QLineEdit *name_player_2 = new QLineEdit();
  layout_name_players->addWidget(name_player_2);
  QLabel *label_player_2_error = new QLabel("Error, enter a name");
  layout_name_players->addWidget(label_player_2_error);
  label_player_2_error->setVisible(false);
  label_player_2_error->setStyleSheet("color: red");

  QSpacerItem *spacer =
      new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
  layout_name_players->addItem(spacer);

  connect(single_player, &QPushButton::clicked, [this, name_player_2, label_player_2, label_player_1_error, label_player_2_error]() {
    name_player_2->setVisible(false);
    label_player_2->setVisible(false);
    label_player_1_error->setVisible(false);
    label_player_2_error->setVisible(false);
    emit number_players_changed(false);
  });
  connect(two_players, &QPushButton::clicked, [this, name_player_2, label_player_2, label_player_1_error, label_player_2_error]() {
    name_player_2->setVisible(true);
    label_player_2->setVisible(true);
    label_player_1_error->setVisible(false);
    label_player_2_error->setVisible(false);
    emit number_players_changed(true);
  });

  layout_players->addWidget(widget_choose_players);
  layout_players->addWidget(widget_name_players);

  widget_players->setGeometry(150, 200, 200, 100);

  // Columna 2
  QWidget *widget_games = new QWidget;
  QVBoxLayout *layout_games = new QVBoxLayout(widget_games);

  game_options->setVisible(true);
  layout_games->addWidget(new QLabel("Select a game:"));
  layout_games->addWidget(game_options);
  QLabel *label_game_name_error = new QLabel("Error, select a game");
  layout_games->addWidget(label_game_name_error);
  label_game_name_error->setVisible(false);
  label_game_name_error->setStyleSheet("color: red");

  QPushButton *update_button = new QPushButton("Update games");
  layout_games->addWidget(update_button);
  connect(update_button, &QPushButton::clicked, this,
          [this,  label_game_name_error]() { 
            label_game_name_error->setVisible(false);
            emit update_games(*this); 
  });
  QPushButton *join_game_button = new QPushButton("Join game");
  layout_games->addWidget(join_game_button);
  connect(join_game_button, &QPushButton::clicked, this, [this, name_player_1, name_player_2, label_player_1_error, label_player_2_error, label_game_name_error]() {
    bool are_fields_empties = false;

    if(name_player_1->text().isEmpty()){
      label_player_1_error->setVisible(true);
      are_fields_empties = true;
    }else{
      label_player_1_error->setVisible(false);
    }

    if(name_player_2->text().isEmpty() && name_player_2->isVisible()){
      label_player_2_error->setVisible(true);
      are_fields_empties = true;
    }else{
      label_player_2_error->setVisible(false);
    }

    if(game_options->currentText().isEmpty()){
      label_game_name_error->setVisible(true);
      are_fields_empties = true;
    }else{
      label_game_name_error->setVisible(false);
    }

    if(!are_fields_empties){
      std::string player_1 = std::string(name_player_1->text().toStdString());
      std::string player_2 = std::string(name_player_2->text().toStdString());
      std::string game = std::string(active_games.take(game_options->currentText()));
      this->close();
      emit join(game, player_1, player_2);
    }
  });
  QPushButton *back_button = new QPushButton("Back");
  connect(back_button, &QPushButton::clicked, this, &Menu::show_main_scene);
  layout_games->addWidget(back_button);

    QSpacerItem *spacer_2 =
      new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
  layout_games->addItem(spacer_2);
  widget_games->setGeometry(400, 200, 200, 100);

  join_game_scene->addWidget(widget_games);
  join_game_scene->addWidget(widget_players);
  join_game_scene->setBackgroundBrush(initial_background);
  view->setScene(join_game_scene);
  view->show();
}

void Menu::show_wait_scene() {
  std::string path =
      std::string(DATA_PATH) + std::string("/menu/Background.jpg");
  QString path_image = QString::fromStdString(path);
  QPixmap initial_background(path_image);
  QWidget *widget_wait = new QWidget;
  QVBoxLayout *layout_wait = new QVBoxLayout(widget_wait);
  layout_wait->addWidget(new QLabel("Waiting for the game to start"));

  QPushButton *start_game = new QPushButton("Start game");
  layout_wait->addWidget(start_game);
  connect(start_game, &QPushButton::clicked, this, [this]() {
    this->close();
    emit start();
  });

  widget_wait->setGeometry(300, 250, 100, 100);
  wait_scene->addWidget(widget_wait);
  wait_scene->setBackgroundBrush(initial_background);
  view->setScene(wait_scene);
  view->show();
}

void Menu::show_update_games(std::list<std::string> active_games) {
  this->active_games.clear();
  game_options->clear();

  for (auto game : active_games) {

    QString game_name = QString::fromStdString(game);

    this->active_games.insert(game_name, game);
    game_options->addItem(game_name);
  }

  show_join_game_scene();
}

void Menu::show_wait(bool is_available_game){
  if(!(is_available_game)){
    std::cout << "El juego esta disponible (Manda 0 si no)" << (int) is_available_game << std::endl;
    show_wait_scene();
  }
}

Menu::~Menu() {}
