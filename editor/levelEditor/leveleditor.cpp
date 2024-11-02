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
        controller->save_map();
        });
        menu.addAction(action_save);
        //Lógica del menu
        menu.addMenu(submenu_backgrounds);
        menu.addMenu(submenu_platform);
        add_submenu_weapons(menu);

        menu.exec(mapToGlobal(pos));
}

void LevelEditor::add_submenu_weapons(QMenu& menu){
    QMenu* submenu_weapons = new QMenu("Weapons", this);

    QAction *action_ak47_weapon = new QAction("ak47", this);
    connect(action_ak47_weapon, &QAction::triggered, [this, action_ak47_weapon]() {
        controller->set_spawn_weapon(action_ak47_weapon->text());
    });
    submenu_weapons->addAction(action_ak47_weapon);

    QAction *action_banana_weapon = new QAction("banana", this);
    connect(action_banana_weapon, &QAction::triggered, [this, action_banana_weapon]() {
        controller->set_spawn_weapon(action_banana_weapon->text());
    });
    submenu_weapons->addAction(action_banana_weapon);

    QAction *action_cowboyPistol_weapon = new QAction("cowboyPistol", this);
    connect(action_cowboyPistol_weapon, &QAction::triggered, [this, action_cowboyPistol_weapon]() {
        controller->set_spawn_weapon(action_cowboyPistol_weapon->text());
    });
    submenu_weapons->addAction(action_cowboyPistol_weapon);

    QAction *action_duelingPistol_weapon = new QAction("duelingPistol", this);
    connect(action_duelingPistol_weapon, &QAction::triggered, [this, action_duelingPistol_weapon]() {
        controller->set_spawn_weapon(action_duelingPistol_weapon->text());
    });
    submenu_weapons->addAction(action_duelingPistol_weapon);

    QAction *action_grenade_weapon = new QAction("grenade", this);
    connect(action_grenade_weapon, &QAction::triggered, [this, action_grenade_weapon]() {
        controller->set_spawn_weapon(action_grenade_weapon->text());
    });
    submenu_weapons->addAction(action_grenade_weapon);

    QAction *action_laserRifle_weapon = new QAction("laserRifle", this);
    connect(action_laserRifle_weapon, &QAction::triggered, [this, action_laserRifle_weapon]() {
        controller->set_spawn_weapon(action_laserRifle_weapon->text());
    });
    submenu_weapons->addAction(action_laserRifle_weapon);

    QAction *action_magnum_weapon = new QAction("magnum", this);
    connect(action_magnum_weapon, &QAction::triggered, [this, action_magnum_weapon]() {
        controller->set_spawn_weapon(action_magnum_weapon->text());
    });
    submenu_weapons->addAction(action_magnum_weapon);

    QAction *action_pewPewLaser_weapon = new QAction("pewPewLaser", this);
    connect(action_pewPewLaser_weapon, &QAction::triggered, [this, action_pewPewLaser_weapon]() {
        controller->set_spawn_weapon(action_pewPewLaser_weapon->text());
    });
    submenu_weapons->addAction(action_pewPewLaser_weapon);

    QAction *action_shotgun_weapon = new QAction("shotgun", this);
    connect(action_shotgun_weapon, &QAction::triggered, [this, action_shotgun_weapon]() {
        controller->set_spawn_weapon(action_shotgun_weapon->text());
    });
    submenu_weapons->addAction(action_shotgun_weapon);

    QAction *action_sniper_weapon = new QAction("sniper", this);
    connect(action_sniper_weapon, &QAction::triggered, [this, action_sniper_weapon]() {
        controller->set_spawn_weapon(action_sniper_weapon->text());
    });
    submenu_weapons->addAction(action_sniper_weapon);

    menu.addMenu(submenu_weapons);
}

LevelEditor::~LevelEditor()
{
    delete ui;
    delete controller;
}

