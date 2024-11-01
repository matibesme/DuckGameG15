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
    Ui::LevelEditor *ui;
    LevelEditorController* controller;

private slots:
    void show_menu_context(const QPoint &pos);
    
};
#endif // LEVELEDITOR_H
