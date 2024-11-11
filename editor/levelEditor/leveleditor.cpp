#include "leveleditor.h"
//#include "./ui_leveleditor.h"
#include <QMenu>
#include <QAction>
#include <QPoint>
#include <QLabel>
#include <QDrag>
#include <QMimeData>
#include <QtWidgets>
#include "leveleditorcontroller.h"


LevelEditor::LevelEditor(QWidget *parent)
    : QMainWindow(parent)
    //, ui(new Ui::LevelEditor)
{
    //ui->setupUi(this);
    this->setGeometry(0, 0, 640, 480);
    initialize();
}

void LevelEditor::initialize(){
    view = new QGraphicsView(this);
    level_editor_scene = new QGraphicsScene(this);
    main_menu_scene = new QGraphicsScene(this);
    controller = new LevelEditorController(*level_editor_scene, this, this);

    view->setGeometry(0, 0, 640, 480);
    main_menu_scene->setSceneRect(0, 0, 640, 480);
    level_editor_scene->setSceneRect(0, 0, 640, 480);

    show_main_menu();
}

void LevelEditor::show_main_menu(){
    std::string path = std::string(DATA_PATH) + std::string("/editor/main_background.png");
    QString path_image = QString::fromStdString(path);
    QPixmap background(path_image);
    main_menu_scene->setBackgroundBrush(background);

    QPushButton* create_level = new QPushButton("Create level");
    create_level->setGeometry(250, 300, 150, 45);
    connect(create_level, &QPushButton::clicked, this, &LevelEditor::show_level_editor);

    QPushButton* edit_level = new QPushButton("Edit level");
    connect(edit_level, &QPushButton::clicked, this, [this]() {
        bool ok;
        QString text = QInputDialog::getText(this, tr("Nombre del mapa"),
                                         tr("Ingrese el nombre del mapa"), QLineEdit::Normal,
                                         "", &ok);
        if(!text.isEmpty()){
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

void LevelEditor::show_level_editor(){
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QMainWindow::customContextMenuRequested, this, &LevelEditor::show_menu_context);
    view->setScene(level_editor_scene);
    view->show();
}

void LevelEditor::show_menu_context(const QPoint &pos){
        QMenu menu(this);
        QMenu* submenu_backgrounds = new QMenu("Backgrounds", this);
        QMenu* submenu_armour = new QMenu("Armour", this);

        //Lógica de submenu del fondo.
        QAction *action_city_background = new QAction("City", this);
        QAction *action_forest_background = new QAction("Forest", this);
        QAction *action_cloudyNight_background = new QAction("Cloudy night", this);
        
        connect(action_city_background, &QAction::triggered,  [this, action_city_background]() {
        controller->set_background(action_city_background->text());
        });
        connect(action_forest_background, &QAction::triggered, [this, action_forest_background]() {
        controller->set_background(action_forest_background->text());
        });

        connect(action_cloudyNight_background, &QAction::triggered, [this, action_cloudyNight_background]() {
        controller->set_background(action_cloudyNight_background->text());
        });

        submenu_backgrounds->addAction(action_city_background);
        submenu_backgrounds->addAction(action_forest_background);
        submenu_backgrounds->addAction(action_cloudyNight_background);

        //Lógica del spawn del pato.
        QAction *action_spawn_duck = new QAction("Spawn", this);
        connect(action_spawn_duck, &QAction::triggered, [this, action_spawn_duck]() {
        controller->set_spawn_duck();
        });
        menu.addAction(action_spawn_duck);

        //Lógica de las cajas
        QAction *action_itemBox_spawn = new QAction("itemBox", this);
        connect(action_itemBox_spawn, &QAction::triggered, [this, action_itemBox_spawn]() {
        controller->set_spawn_box();
        });
        menu.addAction(action_itemBox_spawn);

        //Lógica del submenu de armaduras.
        QAction *action_chestplate_armour = new QAction("chestplate", this);
        connect(action_chestplate_armour, &QAction::triggered, [this, action_chestplate_armour]() {
        controller->set_spawn_armour(action_chestplate_armour->text());
        });
        submenu_armour->addAction(action_chestplate_armour);

        QAction *action_knigthsHelmet_armour = new QAction("knightsHelmet", this);
        connect(action_knigthsHelmet_armour, &QAction::triggered, [this, action_knigthsHelmet_armour]() {
        controller->set_spawn_armour(action_knigthsHelmet_armour->text());
        });
        submenu_armour->addAction(action_knigthsHelmet_armour);

        //Guardado
        QAction *action_save = new QAction("Save", this);
        connect(action_save, &QAction::triggered, [this, action_save]() {
        controller->save_map();
        });
        menu.addAction(action_save);

        //Lógica del menu
        menu.addMenu(submenu_backgrounds);
        menu.addMenu(submenu_armour);
        add_submenu_platforms(menu);
        add_submenu_weapons(menu);
        add_submenu_walls(menu);

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

void LevelEditor::add_submenu_platforms(QMenu& menu){
    QMenu* submenu_platform = new QMenu("Platform", this);

    QAction *action_industrial_platform = new QAction("Industrial", this);
    connect(action_industrial_platform, &QAction::triggered, [this, action_industrial_platform]() {
    controller->set_platform(action_industrial_platform->text());
    });
    submenu_platform->addAction(action_industrial_platform);

    QAction *action_Donut_platform = new QAction("Donut", this);
    connect(action_Donut_platform, &QAction::triggered, [this, action_Donut_platform]() {
    controller->set_platform(action_Donut_platform->text());
    });
    submenu_platform->addAction(action_Donut_platform);

    QAction *action_Nature_platform = new QAction("Nature", this);
    connect(action_Nature_platform, &QAction::triggered, [this, action_Nature_platform]() {
    controller->set_platform(action_Nature_platform->text());
    });
    submenu_platform->addAction(action_Nature_platform);

    QAction *action_Space_platform = new QAction("Space", this);
    connect(action_Space_platform, &QAction::triggered, [this, action_Space_platform]() {
    controller->set_platform(action_Space_platform->text());
    });
    submenu_platform->addAction(action_Space_platform);

    QAction *action_Underground_platform = new QAction("Underground", this);
    connect(action_Underground_platform, &QAction::triggered, [this, action_Underground_platform]() {
    controller->set_platform(action_Underground_platform->text());
    });
    submenu_platform->addAction(action_Underground_platform);

    QAction *action_DonutLarga_platform = new QAction("Donut long", this);
    connect(action_DonutLarga_platform, &QAction::triggered, [this, action_DonutLarga_platform]() {
    controller->set_platform(action_DonutLarga_platform->text());
    });
    submenu_platform->addAction(action_DonutLarga_platform);

    QAction *action_NatureLarga_platform = new QAction("Nature long", this);
    connect(action_NatureLarga_platform, &QAction::triggered, [this, action_NatureLarga_platform]() {
    controller->set_platform(action_NatureLarga_platform->text());
    });
    submenu_platform->addAction(action_NatureLarga_platform);

    menu.addMenu(submenu_platform);
}

void LevelEditor::add_submenu_walls(QMenu& menu){
    QMenu* submenu_walls = new QMenu("Walls", this);

    QAction *action_donut_wall = new QAction("Donut", this);
    connect(action_donut_wall, &QAction::triggered, [this, action_donut_wall]() {
    controller->set_wall(action_donut_wall->text());
    });
    submenu_walls->addAction(action_donut_wall);

    QAction *action_nature_wall = new QAction("Nature", this);
    connect(action_nature_wall, &QAction::triggered, [this, action_nature_wall]() {
    controller->set_wall(action_nature_wall->text());
    });
    submenu_walls->addAction(action_nature_wall);

    QAction *action_underground_wall = new QAction("Underground", this);
    connect(action_underground_wall, &QAction::triggered, [this, action_underground_wall]() {
    controller->set_wall(action_underground_wall->text());
    });
    submenu_walls->addAction(action_underground_wall);


    menu.addMenu(submenu_walls);
}

LevelEditor::~LevelEditor()
{
    //delete ui;
    delete controller;
}

