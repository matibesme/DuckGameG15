#ifndef FINAL_SCENE_H
#define FINAL_SCENE_H

#include <QMainWindow>

class final_scene : public QMainWindow
{
    Q_OBJECT

public:
    final_scene(std::string winner, QWidget *parent = nullptr);
    ~final_scene();
};
#endif // FINAL_SCENE_H
