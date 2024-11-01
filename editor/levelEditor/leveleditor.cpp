#include "leveleditor.h"
#include "./ui_leveleditor.h"
#include <QMenu>
#include <QAction>
#include <QPoint>
#include <QLabel>
#include <QDrag>
#include <QMimeData>
#include "leveleditorcontroller.h"

LevelEditor::LevelEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LevelEditor)
{
    ui->setupUi(this);
    this->setGeometry(0, 0, 640, 480);
    setContextMenuPolicy(Qt::CustomContextMenu);
    controller = new LevelEditorController(this, this);
    connect(this, &QMainWindow::customContextMenuRequested, this, &LevelEditor::show_menu_context);
}

void LevelEditor::show_menu_context(const QPoint &pos){
        QMenu menu(this);
        QMenu* submenu_backgrounds = new QMenu("Backgrounds", this);
        QMenu* submenu_platform = new QMenu("Platform", this);

        //Lógica de submenu del fondo.
        QAction *action_city_background = new QAction("City", this);
        QAction *action_forest_background = new QAction("Forest", this);
        
        connect(action_city_background, &QAction::triggered,  [this, action_city_background]() {
        controller->set_background(action_city_background->text());
        });
        connect(action_forest_background, &QAction::triggered, [this, action_forest_background]() {
        controller->set_background(action_forest_background->text());
        });

        submenu_backgrounds->addAction(action_city_background);
        submenu_backgrounds->addAction(action_forest_background);

        //Lógica del submenu de plataformas.
        QAction *action_industrial_platform = new QAction("Industrial", this);
        connect(action_industrial_platform, &QAction::triggered, [this, action_industrial_platform]() {
        controller->set_platform(action_industrial_platform->text());
        });
        submenu_platform->addAction(action_industrial_platform);

        //Lógica del spawn del pato.
        QAction *action_spawn_duck = new QAction("Spawn", this);
        connect(action_spawn_duck, &QAction::triggered, [this, action_spawn_duck]() {
        controller->set_spawn_duck();
        });
        menu.addAction(action_spawn_duck);

        //Guardado
        QAction *action_save = new QAction("Save", this);
        connect(action_save, &QAction::triggered, [this, action_save]() {
        controller->set_spawn_duck();
        });
        menu.addAction(action_save);
        //Lógica del menu
        menu.addMenu(submenu_backgrounds);
        menu.addMenu(submenu_platform);

        menu.exec(mapToGlobal(pos));
}

LevelEditor::~LevelEditor()
{
    delete ui;
    delete controller;
}

