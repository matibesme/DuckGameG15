#include "FinalScene.h"
#include <QGraphicsView>
#include <QtWidgets>
#include <iostream>
#include <string>

FinalScene::FinalScene(std::string winner, QWidget *parent)
    : QMainWindow(parent){
    /*
    * Usar este código donde se quiera poner la escena:*/


    this->setGeometry(0,0,800,600);
    QGraphicsScene* main_scene = new QGraphicsScene(this);
    QGraphicsView* view = new QGraphicsView(main_scene, this);
    main_scene->setSceneRect(0, 0, 800, 600);
    view->setGeometry(0, 0, 800, 600);

    //Para cambiar al fondo
    std::string background_path_str_ = std::string(DATA_PATH) + std::string("/background/") + std::string("City.png");
    QPixmap initial_background("../final_scene/Forest.png");
    std::string mensage = std::string("The winner is: ") + winner;

    QLabel* mensage_2 = new QLabel(mensage.c_str());
    mensage_2->setStyleSheet("background-color: rgba(255, 255, 255, 128);"
                             "color: black;");
    mensage_2->setGeometry(90, 200, 600, 200);
    mensage_2->setAlignment(Qt::AlignCenter);

    //Para cambiar a la font
    std::string font_path_str = std::string(DATA_PATH) + std::string("/fonts/") + std::string("8-bit-hud.ttf");
    int id = QFontDatabase::addApplicationFont(font_path_str.c_str());
    QString fontFamily;
    if (id != -1) {
        fontFamily = QFontDatabase::applicationFontFamilies(id).at(0);
        QFont customFont(fontFamily, 10);
        mensage_2->setFont(customFont);
    } else {
        qWarning("No se pudo cargar la fuente");
    }
    main_scene->addWidget(mensage_2);

    main_scene->setBackgroundBrush(initial_background);
    view->setScene(main_scene);
    view->show();
}

FinalScene::~FinalScene()
{
}

