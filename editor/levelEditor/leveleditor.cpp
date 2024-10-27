#include "leveleditor.h"
#include "./ui_leveleditor.h"
#include <QMenu>
#include <QAction>
#include <QPoint>
#include <QLabel>
#include <QDrag>
#include <QMimeData>

LevelEditor::LevelEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LevelEditor)
{
    ui->setupUi(this);
    this->setGeometry(0, 0, 640, 480);
     setContextMenuPolicy(Qt::CustomContextMenu);
     connect(this, &QMainWindow::customContextMenuRequested, this, &LevelEditor::show_menu_context);
}

void LevelEditor::show_menu_context(const QPoint &pos){
        QMenu menu(this);
        QMenu* submenu_backgrounds = new QMenu("Backgrounds", this);
        QMenu* submenu_platform = new QMenu("Platform", this);

        //Lógica de submenu del fondo.
        QAction *action_city_background = new QAction("City", this);
        QAction *action_forest_background = new QAction("Forest", this);
        
        connect(action_city_background, &QAction::triggered, this, &LevelEditor::action_1_handler);
        connect(action_forest_background, &QAction::triggered, this, &LevelEditor::action_2_handler);

        submenu_backgrounds->addAction(action_city_background);
        submenu_backgrounds->addAction(action_forest_background);

        //Lógica del submenu de plataformas.
        QAction *action_industrial_platform = new QAction("Industrial", this);
        connect(action_industrial_platform, &QAction::triggered, this, &LevelEditor::action_3_handler);
        submenu_platform->addAction(action_industrial_platform);

        //Lógica del menu
        menu.addMenu(submenu_backgrounds);
        menu.addMenu(submenu_platform);

        menu.exec(mapToGlobal(pos));
}

void LevelEditor::action_1_handler(){
    this->setGeometry(0, 0, 640, 480);

    QPalette pal;

    QPixmap fondo("../../data/city.png");

    QBrush brush(fondo);
    pal.setBrush(QPalette::Window, brush);
    this->setPalette(pal);
    this->setAutoFillBackground(true);

    this->show();
}

void LevelEditor::action_2_handler(){
    this->setGeometry(0, 0, 640, 480);

    QPalette pal;

    QPixmap fondo("../../data/forest.png");

    QBrush brush(fondo);
    pal.setBrush(QPalette::Window, brush);
    this->setPalette(pal);
    this->setAutoFillBackground(true);

    this->show();
}

void LevelEditor::action_3_handler(){
    QLabel *platform_label = new QLabel(this);
    QPixmap platform_industrial("../../data/plataforma_prueba.png");
    platform_label->setPixmap(platform_industrial); 
    platform_label->setGeometry(100, 100, 32, 15);
    platform_label->setAcceptDrops(true);
    platform_label->show();

    QDrag *drag = new QDrag(this);
    QMimeData *mime_data = new QMimeData;

    mime_data->setImageData(platform_industrial.toImage());
    drag->setMimeData(mime_data);
    drag->setPixmap(platform_industrial);

    Qt::DropAction drop_action = drag->exec();
    
}

LevelEditor::~LevelEditor()
{
    delete ui;
}

