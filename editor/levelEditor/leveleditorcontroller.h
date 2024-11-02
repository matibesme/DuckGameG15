#ifndef LEVEL_EDITOR_CONTROLLER_H
#define LEVEL_EDITOR_CONTROLLER_H
#include "mapobject.h"
#include "pathmaker.h"

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QList>

class LevelEditorController : public QObject {
    Q_OBJECT
private:
    QMainWindow* window;
    QGraphicsScene *scene;
    QGraphicsView *view;
    std::string background_type;
    QList<MapObject*> platforms;
    QList<MapObject*> guns;
    QList<MapObject*> boxes;
    PathMaker path_maker;

public:
    LevelEditorController(QMainWindow *window, QObject *parent = nullptr);
    void set_background(const QString &background_type);
    void set_platform(const QString &platform_type);
    void set_spawn_duck();
    /*void set_spawn_gun(const QString &gun_type);*/
    void set_spawn_box();
    void save_map();
};

#endif