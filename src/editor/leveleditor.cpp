#include "leveleditor.h"
// #include "./ui_leveleditor.h"
#include "leveleditorcontroller.h"
#include <QAction>
#include <QDrag>
#include <QLabel>
#include <QMenu>
#include <QMimeData>
#include <QPoint>
#include <QtWidgets>
#include <string>
#include <yaml-cpp/yaml.h>
static const char *CONFIG_MENU_YAML_REL_PATH = "/menu_config.yaml";

LevelEditor::LevelEditor(QWidget *parent) : QMainWindow(parent) {
  this->setGeometry(0, 0, 640, 480);
  initialize();
}

void LevelEditor::initialize() {
  view = new QGraphicsView(this);
  level_editor_scene = new QGraphicsScene(this);
  main_menu_scene = new QGraphicsScene(this);
  controller = new LevelEditorController(*level_editor_scene, this, this);

  view->setGeometry(0, 0, 640, 480);
  main_menu_scene->setSceneRect(0, 0, 640, 480);
  level_editor_scene->setSceneRect(0, 0, 640, 480);

  show_main_menu();
}

void LevelEditor::show_main_menu() {
  std::string path =
      std::string(DATA_PATH) + std::string("/editor/main_background.png");
  QString path_image = QString::fromStdString(path);
  QPixmap background(path_image);
  main_menu_scene->setBackgroundBrush(background);

  QPushButton *create_level = new QPushButton("Create level");
  create_level->setGeometry(250, 300, 150, 45);
  connect(create_level, &QPushButton::clicked, this,
          &LevelEditor::show_level_editor);

  QPushButton *edit_level = new QPushButton("Edit level");
  connect(edit_level, &QPushButton::clicked, this, [this]() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Nombre del mapa"),
                                         tr("Ingrese el nombre del mapa"),
                                         QLineEdit::Normal, "", &ok);
    if (!text.isEmpty()) {
      controller->load_map(text.toStdString());
      show_level_editor();
    }
  });
  edit_level->setGeometry(250, 350, 150, 45);

  main_menu_scene->addWidget(create_level);
  main_menu_scene->addWidget(edit_level);
  view->setScene(main_menu_scene);
  view->show();
}

void LevelEditor::show_level_editor() {
  setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, &QMainWindow::customContextMenuRequested, this,
          &LevelEditor::initialize_menus);
  controller->set_default_duck_spawn();
  view->setScene(level_editor_scene);
  view->show();
}
void LevelEditor::initialize_menus(const QPoint &pos) {
  QMenu menu(this);
  std::string yaml_path =
      std::string(CONFIG_PATH) + std::string(CONFIG_MENU_YAML_REL_PATH);
  YAML::Node file = YAML::LoadFile(yaml_path);

  for (const auto &submenu : file) {
    QString submenu_name =
        QString::fromStdString(submenu.first.as<std::string>());
    QMenu *submenu_option = new QMenu(submenu_name, &menu);

    for (const auto &option : submenu.second) {
      QAction *action = new QAction(
          QString::fromStdString(option.as<std::string>()), submenu_option);
      connect(action, &QAction::triggered,
              [this, action, submenu_option, submenu_name, pos]() {
                QString action_name = action->text();
                if (submenu_name == "Weapons") {
                  controller->set_spawn_weapon(action_name, pos.x(), pos.y());
                } else if (submenu_name == "Platforms") {
                  controller->set_platform(action_name, pos.x(), pos.y());
                } else if (submenu_name == "Walls") {
                  controller->set_wall(action_name, pos.x(), pos.y());
                } else if (submenu_name == "Backgrounds") {
                  controller->set_background(action_name);
                } else if (submenu_name == "Armour") {
                  controller->set_spawn_armour(action_name, pos.x(), pos.y());
                }
              });
      submenu_option->addAction(action);
    }

    menu.addMenu(submenu_option);
  }

  /*QAction *action_spawn_duck = new QAction("Spawn", this);
  connect(action_spawn_duck, &QAction::triggered, [this, action_spawn_duck]() {
  controller->set_spawn_duck();
  });
  menu.addAction(action_spawn_duck);*/

  QAction *action_itemBox_spawn = new QAction("itemBox", this);
  connect(action_itemBox_spawn, &QAction::triggered,
          [this, action_itemBox_spawn, pos]() {
            controller->set_spawn_box(pos.x(), pos.y());
          });
  menu.addAction(action_itemBox_spawn);

  QAction *action_save = new QAction("Save", this);
  connect(action_save, &QAction::triggered,
          [this, action_save]() { controller->save_map(); });
  menu.addAction(action_save);

  menu.exec(mapToGlobal(pos));
}

LevelEditor::~LevelEditor() {
  // delete ui;
  delete controller;
}
