#ifndef TALLER_TP_PANTALLAVICTORIA_H
#define TALLER_TP_PANTALLAVICTORIA_H

#include <string>
#include "SDL2pp/SDL2pp.hh"
#include "Graficos.h"


class PantallaVictoria {
private:
  std::string duckName;
  Graficos &graficos;
  void draw();
public:
  explicit PantallaVictoria(std::string name, Graficos& graficos);

};

#endif // TALLER_TP_PANTALLAVICTORIA_H
