#ifndef FINAL_SCENE_H
#define FINAL_SCENE_H

#include <QMainWindow>

class FinalScene : public QMainWindow
{
    Q_OBJECT

public:
  FinalScene(std::string winner, QWidget *parent = nullptr);
  ~FinalScene();
};
#endif // FINAL_SCENE_H
