#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <QMainWindow>
#include <QMenu>
#include "leveleditorcontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LevelEditor; }
QT_END_NAMESPACE

class LevelEditor : public QMainWindow
{
    Q_OBJECT

public:
    LevelEditor(QWidget *parent = nullptr);
    ~LevelEditor();

private:
    QGraphicsScene *main_menu_scene;
    QGraphicsScene *level_editor_scene;
    QGraphicsView *view;
    LevelEditorController* controller;
    void add_submenu_weapons(QMenu& menu);
    void add_submenu_platforms(QMenu& menu);
    void add_submenu_walls(QMenu& menu);
    void initialize();
    void show_main_menu();
    void show_level_editor();

private slots:
    void show_menu_context(const QPoint &pos);
    
};
#endif
