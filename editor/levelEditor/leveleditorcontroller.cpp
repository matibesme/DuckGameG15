#include "leveleditorcontroller.h"
#include "mapobject.h"

#include <QPalette>
#include <QPixmap>
#include <QBrush>
#include <QDrag>
#include <QMimeData>
#include <QMainWindow>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <iostream>

LevelEditorController::LevelEditorController(QMainWindow *window, QObject *parent) :  QObject(parent), window(window){
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, window);

    view->setGeometry(0, 0, 640, 480);
    scene->setSceneRect(0, 0, 640, 480);
    view->setScene(scene);
    view->show();
}

void LevelEditorController::set_background(const QString &background_name){
    QString background_path;

    if (background_name.toStdString() == "City") {
        background_path = "data/city.png";
    } else if (background_name.toStdString() == "Forest") {
        background_path = "data/forest.png";
    }

    QPixmap background(background_path);
    scene->setBackgroundBrush(background);
    background_type = background_name.toStdString();

}

void LevelEditorController::set_platform(const QString &platform_type){
    QString platform_path;

    if (platform_type.toStdString() == "Industrial") {
        platform_path = "data/plataforma_prueba.png";
        
    }
    QPixmap platform(platform_path);
    MapObject* platform_item = new MapObject(platform, "Industrial");
    
    platform_item->setPos(100, 100);
    scene->addItem(platform_item);
    platforms.push_back(platform_item);
}

void LevelEditorController::set_spawn_duck(){

}

/*void LevelEditorController::set_spawn_gun(const QString &gun_type){

}*/
void LevelEditorController::set_spawn_box(){

}

void LevelEditorController::save_map(){
    YAML::Emitter out;

    out << YAML::BeginMap;
    out << YAML::Key << "background_type";
    out << YAML::Value << background_type;

    out << YAML::Key << "plataforms";
    out << YAML::Value << YAML::BeginSeq;
    std::cout << "El tamaño de la lista es: " << platforms.size();
    for(int i = 0; i < platforms.size(); i++){
        out << YAML::BeginMap;
        out << YAML::Key << "pos_x";
        out << YAML::Value << platforms.at(i)->x();
        out << YAML::Key << "pos_y";
        out << YAML::Value << platforms.at(i)->y();
        out << YAML::Key << "height";
        out << YAML::Value <<  platforms.at(i)->pixmap().height();
        out << YAML::Key << "width";
        out << YAML::Value << platforms.at(i)->pixmap().width();
        out << YAML::Key << "type";
        out << YAML::Value << platforms.at(i)->get_type().toStdString();
        out << YAML::EndMap;
    }
    out << YAML::EndSeq;
    out << YAML::EndMap;

    std::ofstream fout("a_map.yaml");
    fout << out.c_str();
}
