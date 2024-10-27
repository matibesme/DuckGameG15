#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <QMainWindow>
#include <QMenu>

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

private slots:
    void show_menu_context(const QPoint &pos);
    void action_1_handler();
    void action_2_handler();
    void action_3_handler();
    
};
#endif // LEVELEDITOR_H
