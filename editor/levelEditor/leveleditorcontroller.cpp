#include "leveleditorcontroller.h"
#include "mapobject.h"

#include <QPalette>
#include <QPixmap>
#include <QBrush>
#include <QDrag>
#include <QMimeData>
#include <QMainWindow>


LevelEditorController::LevelEditorController(QMainWindow *window, QObject *parent) :  QObject(parent), window(window){
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, window);

    view->setGeometry(0, 0, 640, 480);
    scene->setSceneRect(0, 0, 640, 480);
    view->setScene(scene);
    view->show();
}

void LevelEditorController::set_background(const QString &backgroundName){
    QString background_path;

    if (backgroundName == "City") {
        background_path = "data/city.png";
    } else if (backgroundName == "Forest") {
        background_path = "data/forest.png";
    }

    QPixmap background(background_path);
    scene->setBackgroundBrush(background);

}

void LevelEditorController::set_platform(const QString &platform_type){
    QString platform_path;

    if (platform_type == "Industrial") {
        platform_path = "data/plataforma_prueba.png";
        
    }
    QPixmap platform(platform_path);
    MapObject* platformItem = new MapObject(platform, "industrial");
    
    platformItem->setPos(100, 100);
    scene->addItem(platformItem);
    
}

void LevelEditorController::set_spawn_duck(){

}

void LevelEditorController::set_spawn_gun(const QString &platform_type){

}
void LevelEditorController::set_spawn_box(){

}

void LevelEditorController::save_map(){
    
}
