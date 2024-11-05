#include "leveleditorcontroller.h"
#include "mapobject.h"
#include "pathmaker.h"
#include "idmaker.h"

#include <QPalette>
#include <QPixmap>
#include <QBrush>
#include <QDrag>
#include <QMimeData>
#include <QMainWindow>
#include <QInputDialog>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <iostream>

LevelEditorController::LevelEditorController(QMainWindow *window, QObject *parent) :  QObject(parent), window(window){
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, window);

    view->setGeometry(0, 0, 640, 480);
    scene->setSceneRect(0, 0, 640, 480);
    std::string background_type("");
    view->setScene(scene);
    view->show();
}

void LevelEditorController::set_background(const QString &background_name){
    QString background_path = QString::fromStdString(path_maker.get_background_path(background_name.toStdString()));

    QPixmap background(background_path);
    scene->setBackgroundBrush(background);
    background_type = background_name.toStdString();

}

void LevelEditorController::set_platform(const QString &platform_type){
    QString platform_path = QString::fromStdString(path_maker.get_platform_path(platform_type.toStdString()));;

    QPixmap platform(platform_path);
    MapObject* platform_item = new MapObject(platform, platform_type);
    
    platform_item->setPos(100, 100);
    scene->addItem(platform_item);
    platforms.push_back(platform_item);
}

void LevelEditorController::set_spawn_duck(){
    QString duck_path = QString::fromStdString(std::string(DATA_PATH) + std::string("/whiteDuck.png"));

    QRect rect(0, 7, 32, 24);
    QPixmap sprite(duck_path);
    QPixmap duck = sprite.copy(rect);

    QGraphicsPixmapItem* duck_spawn = new QGraphicsPixmapItem(duck);
    duck_spawn->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    duck_spawn->setPos(100, 100);
    scene->addItem(duck_spawn);
    duck_spawns.push_back(duck_spawn);

}

void LevelEditorController::set_spawn_weapon(const QString &gun_type){
    QString weapon_path = QString::fromStdString(path_maker.get_weapon_path(gun_type.toStdString()));;

    QPixmap weapon(weapon_path);
    MapObject* weapon_item = new MapObject(weapon, gun_type);
    
    weapon_item->setPos(100, 100);
    scene->addItem(weapon_item);
    weapons.push_back(weapon_item);
}

void LevelEditorController::set_spawn_box(){
    QString box_path = QString::fromStdString(std::string(DATA_PATH) + std::string("/objects/itemBox.png"));
    QPixmap box(box_path);

    QGraphicsPixmapItem* box_spawn = new QGraphicsPixmapItem(box);
    box_spawn->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    box_spawn->setPos(100, 100);
    scene->addItem(box_spawn);
    boxes.push_back(box_spawn);
}

void LevelEditorController::set_spawn_armour(const QString &armour_type){
    QString armour_path = QString::fromStdString(path_maker.get_armour_path(armour_type.toStdString()));;

    QPixmap armour(armour_path);
    MapObject* armour_item = new MapObject(armour, armour_type);
    
    armour_item->setPos(100, 100);
    scene->addItem(armour_item);
    armours.push_back(armour_item);
}

void LevelEditorController::set_wall(const QString &wall_type){
    QString wall_path = QString::fromStdString(path_maker.get_wall_path(wall_type.toStdString()));;

    QPixmap wall(wall_path);
    MapObject* wall_item = new MapObject(wall, wall_type);

    wall_item->setPos(100, 100);
    scene->addItem(wall_item);
    walls.push_back(wall_item);
}

void LevelEditorController::save_map(){
    bool ok;
    QString text = QInputDialog::getText(window, tr("Nombre del mapa"),
                                         tr("Ingrese el nombre del mapa"), QLineEdit::Normal,
                                         "", &ok);

    YAML::Emitter out;

    out << YAML::BeginMap;
    out << YAML::Key << "background_type";
    out << YAML::Value << id_maker.get_id_background(background_type);

    out << YAML::Key << "plataforms";
    out << YAML::Value << YAML::BeginSeq;
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
        out << YAML::Value << id_maker.get_id_platform(platforms.at(i)->get_type().toStdString());
        out << YAML::EndMap;
    }
    out << YAML::EndSeq;

    out << YAML::Key << "walls";
    out << YAML::Value << YAML::BeginSeq;
    for(int i = 0; i < walls.size(); i++){
        out << YAML::BeginMap;
        out << YAML::Key << "pos_x";
        out << YAML::Value << walls.at(i)->x();
        out << YAML::Key << "pos_y";
        out << YAML::Value << walls.at(i)->y();
        out << YAML::Key << "height";
        out << YAML::Value <<  walls.at(i)->pixmap().height();
        out << YAML::Key << "width";
        out << YAML::Value << walls.at(i)->pixmap().width();
        out << YAML::Key << "type";
        out << YAML::Value << id_maker.get_id_wall(walls.at(i)->get_type().toStdString());
        out << YAML::EndMap;
    }
    out << YAML::EndSeq;

    out << YAML::Key << "duck spawns";
    out << YAML::Value << YAML::BeginSeq;
    for(int i = 0; i < duck_spawns.size(); i++){
        out << YAML::BeginMap;
        out << YAML::Key << "pos_x";
        out << YAML::Value << duck_spawns.at(i)->x();
        out << YAML::Key << "pos_y";
        out << YAML::Value << duck_spawns.at(i)->y();
        out << YAML::Key << "height";
        out << YAML::Value << duck_spawns.at(i)->pixmap().height();
        out << YAML::Key << "width";
        out << YAML::Value << duck_spawns.at(i)->pixmap().width();
        out << YAML::EndMap;
    }
    out << YAML::EndSeq;

    out << YAML::Key << "weapon spawns";
    out << YAML::Value << YAML::BeginSeq;
    for(int i = 0; i < weapons.size(); i++){
        out << YAML::BeginMap;
        out << YAML::Key << "pos_x";
        out << YAML::Value << weapons.at(i)->x();
        out << YAML::Key << "pos_y";
        out << YAML::Value << weapons.at(i)->y();
        out << YAML::Key << "height";
        out << YAML::Value << weapons.at(i)->pixmap().height();
        out << YAML::Key << "width";
        out << YAML::Value << weapons.at(i)->pixmap().width();
        out << YAML::Key << "type";
        out << YAML::Value << id_maker.get_id_weapon(weapons.at(i)->get_type().toStdString());
        out << YAML::EndMap;
    }
    out << YAML::EndSeq;

    out << YAML::Key << "box spawns";
    out << YAML::Value << YAML::BeginSeq;
    for(int i = 0; i < boxes.size(); i++){
        out << YAML::BeginMap;
        out << YAML::Key << "pos_x";
        out << YAML::Value << boxes.at(i)->x();
        out << YAML::Key << "pos_y";
        out << YAML::Value << boxes.at(i)->y();
        out << YAML::Key << "height";
        out << YAML::Value << boxes.at(i)->pixmap().height();
        out << YAML::Key << "width";
        out << YAML::Value << boxes.at(i)->pixmap().width();
        out << YAML::EndMap;
    }
    out << YAML::EndMap;

    out << YAML::Key << "armour spawns";
    out << YAML::Value << YAML::BeginSeq;
    for(int i = 0; i < armours.size(); i++){
        out << YAML::BeginMap;
        out << YAML::Key << "pos_x";
        out << YAML::Value << armours.at(i)->x();
        out << YAML::Key << "pos_y";
        out << YAML::Value << armours.at(i)->y();
        out << YAML::Key << "height";
        out << YAML::Value << armours.at(i)->pixmap().height();
        out << YAML::Key << "width";
        out << YAML::Value << armours.at(i)->pixmap().width();
        out << YAML::Key << "type";
        out << YAML::Value << id_maker.get_id_armour(armours.at(i)->get_type().toStdString());
        out << YAML::EndMap;
    }
    out << YAML::EndSeq;

    if (ok){
        if(!(text.isEmpty())){
            std::string file_name = std::string(DATA_PATH) + std::string("/maps/") + std::string(text.toStdString()) + std::string(".yaml");
            std::ofstream fout(file_name);
            fout << out.c_str();
        }else{
            std::string file_name = std::string(DATA_PATH) + std::string("/maps/") + std::string("a_map.yaml");
            std::ofstream fout(file_name);
            fout << out.c_str();
        }
        
    }
    
    
}
