#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include "leveleditorcontroller.h"
#include <QMainWindow>
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui {
class LevelEditor;
}
QT_END_NAMESPACE

class LevelEditor : public QMainWindow {
  Q_OBJECT

public:
  LevelEditor(QWidget *parent = nullptr);
  ~LevelEditor();

private:
  QGraphicsScene *main_menu_scene;
  QGraphicsScene *level_editor_scene;
  QGraphicsView *view;
  LevelEditorController *controller;
  void initialize();
  void show_main_menu();
  void show_level_editor();

private slots:
  void initialize_menus(const QPoint &pos);
};
#endif
