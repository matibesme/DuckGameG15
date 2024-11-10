#ifndef LEVEL_EDITOR_CONTROLLER_H
#define LEVEL_EDITOR_CONTROLLER_H
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QList>
#include <QMainWindow>

#include "idmaker.h"
#include "mapobject.h"
#include "pathmaker.h"

class LevelEditorController: public QObject {
    Q_OBJECT
private:
    QMainWindow* window;
    QGraphicsScene* scene;
    QGraphicsView* view;
    std::string background_type;
    QList<QGraphicsPixmapItem*> duck_spawns;
    QList<MapObject*> platforms;
    QList<MapObject*> weapons;
    QList<MapObject*> armours;
    QList<MapObject*> walls;
    QList<QGraphicsPixmapItem*> boxes;
    PathMaker path_maker;
    IDMaker id_maker;

public:
    LevelEditorController(QMainWindow* window, QObject* parent = nullptr);
    void set_background(const QString& background_type);
    void set_platform(const QString& platform_type);
    void set_spawn_duck();
    void set_spawn_weapon(const QString& weapon_type);
    void set_spawn_armour(const QString& armour_type);
    void set_spawn_box();
    void set_wall(const QString& wall_type);
    void save_map();
};

#endif