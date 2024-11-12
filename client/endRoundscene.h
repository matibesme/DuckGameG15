#ifndef TALLER_TP_ENDROUNDSCENE_H
#define TALLER_TP_ENDROUNDSCENE_H

#include <QMainWindow>

class EndRoundScene : public QMainWindow {
  Q_OBJECT

public:
  EndRoundScene(std::map< std::string, uint8_t > &players, QWidget *parent = nullptr);
  ~EndRoundScene();
};

#endif // TALLER_TP_ENDROUNDSCENE_H
