#ifndef LEVEL_EDITOR_CONTROLLER_H
#define LEVEL_EDITOR_CONTROLLER_H
#include "idmaker.h"
#include "mapobject.h"
#include "pathmaker.h"
#include "typemaker.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QList>
#include <QMainWindow>

static const int DEFAULT_POS_X = 100;
static const int DEFAULT_POS_Y = 100;

class LevelEditorController : public QObject {
  Q_OBJECT
private:
  QMainWindow *window;
  QGraphicsScene &scene;
  std::string background_type;
  QList<QGraphicsPixmapItem *> duck_spawns;
  QList<MapObject *> platforms;
  QList<MapObject *> weapons;
  QList<MapObject *> armours;
  QList<MapObject *> walls;
  QList<QGraphicsPixmapItem *> boxes;
  PathMaker path_maker;
  IDMaker id_maker;
  TypeMaker type_maker;

public:
  LevelEditorController(QGraphicsScene &scene, QMainWindow *window,
                        QObject *parent = nullptr);
  void set_background(const QString &background_type);
  void set_platform(const QString &platform_type, int pos_x = DEFAULT_POS_X,
                    int pos_y = DEFAULT_POS_Y);
  void set_spawn_duck(int pos_x = DEFAULT_POS_X, int pos_y = DEFAULT_POS_Y);
  void set_spawn_weapon(const QString &weapon_type, int pos_x = DEFAULT_POS_X,
                        int pos_y = DEFAULT_POS_Y);
  void set_spawn_armour(const QString &armour_type, int pos_x = DEFAULT_POS_X,
                        int pos_y = DEFAULT_POS_Y);
  void set_spawn_box(int pos_x = DEFAULT_POS_X, int pos_y = DEFAULT_POS_Y);
  void set_wall(const QString &wall_type, int pos_x = DEFAULT_POS_X,
                int pos_y = DEFAULT_POS_Y);
  void load_map(const std::string path_map);
  void save_map();
};

#endif