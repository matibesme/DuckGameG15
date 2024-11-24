#include "leveleditorcontroller.h"
#include "idmaker.h"
#include "mapobject.h"
#include "pathmaker.h"

#include <QBrush>
#include <QDrag>
#include <QInputDialog>
#include <QMainWindow>
#include <QMimeData>
#include <QPalette>
#include <QPixmap>
#include <fstream>
#include <iostream>
#include <yaml-cpp/yaml.h>

LevelEditorController::LevelEditorController(QGraphicsScene &scene,
                                             QMainWindow *window,
                                             QObject *parent)
    : QObject(parent), window(window), scene(scene) {
  this->background_type = "";
}

void LevelEditorController::set_background(const QString &background_name) {
  QString background_path = QString::fromStdString(
      path_maker.get_background_path(background_name.toStdString()));

  QPixmap background(background_path);
  scene.setBackgroundBrush(background);
  background_type = background_name.toStdString();
}

void LevelEditorController::set_platform(const QString &platform_type,
                                         int pos_x, int pos_y) {
  QString platform_path = QString::fromStdString(
      path_maker.get_platform_path(platform_type.toStdString()));

  QPixmap platform(platform_path);
  MapObject *platform_item = new MapObject(platform, platform_type);

  platform_item->setPos(pos_x, pos_y);
  scene.addItem(platform_item);
  platforms.push_back(platform_item);
}

void LevelEditorController::set_spawn_duck(int pos_x, int pos_y) {
  QString duck_path = QString::fromStdString(std::string(DATA_PATH) +
                                             std::string("/objects/Duck.png"));

  QRect rect(0, 7, 32, 24);
  QPixmap sprite(duck_path);
  QPixmap duck = sprite.copy(rect);

  QGraphicsPixmapItem *duck_spawn = new QGraphicsPixmapItem(duck);
  duck_spawn->setFlags(QGraphicsItem::ItemIsMovable |
                       QGraphicsItem::ItemIsSelectable);
  duck_spawn->setPos(pos_x, pos_y);
  scene.addItem(duck_spawn);
  duck_spawns.push_back(duck_spawn);
}

void LevelEditorController::set_spawn_weapon(const QString &gun_type, int pos_x,
                                             int pos_y) {
  QString weapon_path = QString::fromStdString(
      path_maker.get_weapon_path(gun_type.toStdString()));

  QPixmap weapon(weapon_path);
  MapObject *weapon_item = new MapObject(weapon, gun_type);

  weapon_item->setPos(pos_x, pos_y);
  scene.addItem(weapon_item);
  weapons.push_back(weapon_item);
}

void LevelEditorController::set_spawn_box(int pos_x, int pos_y) {
  QString box_path = QString::fromStdString(
      std::string(DATA_PATH) + std::string("/objects/itemBox.png"));
  QPixmap box(box_path);

  // QGraphicsPixmapItem *box_spawn = new QGraphicsPixmapItem(box);
  /*box_spawn->setFlags(QGraphicsItem::ItemIsMovable |
                      QGraphicsItem::ItemIsSelectable);*/
  MapObject *box_spawn = new MapObject(box, "itemBox");
  box_spawn->setPos(pos_x, pos_y);
  scene.addItem(box_spawn);
  boxes.push_back(box_spawn);
}

void LevelEditorController::set_spawn_armour(const QString &armour_type,
                                             int pos_x, int pos_y) {
  QString armour_path = QString::fromStdString(
      path_maker.get_armour_path(armour_type.toStdString()));

  QPixmap armour(armour_path);
  MapObject *armour_item = new MapObject(armour, armour_type);

  armour_item->setPos(pos_x, pos_y);
  scene.addItem(armour_item);
  armours.push_back(armour_item);
}

void LevelEditorController::set_wall(const QString &wall_type, int pos_x,
                                     int pos_y) {
  QString wall_path =
      QString::fromStdString(path_maker.get_wall_path(wall_type.toStdString()));

  QPixmap wall(wall_path);
  MapObject *wall_item = new MapObject(wall, wall_type);

  wall_item->setPos(pos_x, pos_y);
  scene.addItem(wall_item);
  walls.push_back(wall_item);
}

void LevelEditorController::save_map() {
  bool ok;
  QString text = QInputDialog::getText(window, tr("Nombre del mapa"),
                                       tr("Ingrese el nombre del mapa"),
                                       QLineEdit::Normal, "", &ok);

  YAML::Emitter out;

  out << YAML::BeginMap;
  out << YAML::Key << "background_type";
  out << YAML::Value << id_maker.get_id_background(background_type);

  out << YAML::Key << "plataforms";
  out << YAML::Value << YAML::BeginSeq;
  for (int i = 0; i < platforms.size(); i++) {
    if (platforms.at(i)->isVisible()) {
      out << YAML::BeginMap;
      out << YAML::Key << "pos_x";
      out << YAML::Value << platforms.at(i)->x();
      out << YAML::Key << "pos_y";
      out << YAML::Value << platforms.at(i)->y();
      out << YAML::Key << "height";
      out << YAML::Value << platforms.at(i)->pixmap().height();
      out << YAML::Key << "width";
      out << YAML::Value << platforms.at(i)->pixmap().width();
      out << YAML::Key << "type";
      out << YAML::Value
          << id_maker.get_id_platform(
                 platforms.at(i)->get_type().toStdString());
      out << YAML::EndMap;
    }
  }
  out << YAML::EndSeq;

  out << YAML::Key << "walls";
  out << YAML::Value << YAML::BeginSeq;
  for (int i = 0; i < walls.size(); i++) {
    if (walls.at(i)->isVisible()) {
      out << YAML::BeginMap;
      out << YAML::Key << "pos_x";
      out << YAML::Value << walls.at(i)->x();
      out << YAML::Key << "pos_y";
      out << YAML::Value << walls.at(i)->y();
      out << YAML::Key << "height";
      out << YAML::Value << walls.at(i)->pixmap().height();
      out << YAML::Key << "width";
      out << YAML::Value << walls.at(i)->pixmap().width();
      out << YAML::Key << "type";
      out << YAML::Value
          << id_maker.get_id_wall(walls.at(i)->get_type().toStdString());
      out << YAML::EndMap;
    }
  }
  out << YAML::EndSeq;

  out << YAML::Key << "duck spawns";
  out << YAML::Value << YAML::BeginSeq;
  for (int i = 0; i < duck_spawns.size(); i++) {
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
  for (int i = 0; i < weapons.size(); i++) {
    if (weapons.at(i)->isVisible()) {
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
      out << YAML::Value
          << id_maker.get_id_weapon(weapons.at(i)->get_type().toStdString());
      out << YAML::EndMap;
    }
  }
  out << YAML::EndSeq;

  out << YAML::Key << "box spawns";
  out << YAML::Value << YAML::BeginSeq;
  for (int i = 0; i < boxes.size(); i++) {
    if (boxes.at(i)->isVisible()) {
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
  }
  out << YAML::EndSeq;

  out << YAML::Key << "armour spawns";
  out << YAML::Value << YAML::BeginSeq;
  for (int i = 0; i < armours.size(); i++) {
    if (armours.at(i)->isVisible()) {
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
      out << YAML::Value
          << id_maker.get_id_armour(armours.at(i)->get_type().toStdString());
      out << YAML::EndMap;
    }
  }
  out << YAML::EndSeq;
  out << YAML::EndMap;

  if (ok) {
    if (!(text.isEmpty())) {
      std::string file_name = std::string(DATA_PATH) + std::string("/maps/") +
                              std::string(text.toStdString()) +
                              std::string(".yaml");
      std::ofstream fout(file_name);
      std::cout << "El path es: " << file_name << std::endl;
      fout << out.c_str();
    } else {
      std::string file_name = std::string(DATA_PATH) + std::string("/maps/") +
                              std::string("a_map.yaml");
      std::ofstream fout(file_name);
      fout << out.c_str();
    }
  }
}

void LevelEditorController::load_map(const std::string &path_map) {
  std::string path = std::string(DATA_PATH) + std::string("/maps/") +
                     std::string(path_map) + std::string(".yaml");
  YAML::Node map = YAML::LoadFile(path);

  QString background_name = QString::fromStdString(
      type_maker.get_type_background(map["background_type"].as<uint8_t>()));
  set_background(background_name);

  if (map["plataforms"]) {
    for (const auto &platform : map["plataforms"]) {
      int pos_x = platform["pos_x"].as<int>();
      int pos_y = platform["pos_y"].as<int>();
      QString type = QString::fromStdString(
          type_maker.get_type_platform(platform["type"].as<uint8_t>()));
      set_platform(type, pos_x, pos_y);
    }
  }

  if (map["walls"]) {
    for (const auto &walls : map["walls"]) {
      int pos_x = walls["pos_x"].as<int>();
      int pos_y = walls["pos_y"].as<int>();
      QString type = QString::fromStdString(
          type_maker.get_type_wall(walls["type"].as<uint8_t>()));
      set_wall(type, pos_x, pos_y);
    }
  }

  if (map["duck spawns"]) {
    for (const auto &duck_spawns : map["duck spawns"]) {
      int pos_x = duck_spawns["pos_x"].as<int>();
      int pos_y = duck_spawns["pos_y"].as<int>();
      set_spawn_duck(pos_x, pos_y);
    }
  }

  if (map["weapon spawns"]) {
    for (const auto &weapon : map["weapon spawns"]) {
      int pos_x = weapon["pos_x"].as<int>();
      int pos_y = weapon["pos_y"].as<int>();
      QString type = QString::fromStdString(
          type_maker.get_type_weapon(weapon["type"].as<uint8_t>()));
      set_spawn_weapon(type, pos_x, pos_y);
    }
  }

  if (map["box spawns"]) {
    for (const auto &box : map["box spawns"]) {
      int pos_x = box["pos_x"].as<int>();
      int pos_y = box["pos_y"].as<int>();
      set_spawn_box(pos_x, pos_y);
    }
  }

  if (map["armour spawns"]) {
    for (const auto &armour : map["armour spawns"]) {
      int pos_x = armour["pos_x"].as<int>();
      int pos_y = armour["pos_y"].as<int>();
      QString type = QString::fromStdString(
          type_maker.get_type_armour(armour["type"].as<uint8_t>()));
      set_spawn_armour(type, pos_x, pos_y);
    }
  }
}

void LevelEditorController::set_default_duck_spawn() {
  if (duck_spawns.isEmpty()) {
    set_spawn_duck();
  }
}
