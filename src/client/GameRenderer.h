#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include <list>

#include "Graficos.h"
#include "Items/Box.h"
#include "Items/Bullet.h"
#include "Items/ClientDuck.h"
#include "Items/Gun.h"
#include "Items/Platform.h"
#include "Items/armor.h"
#include "Items/helmet.h"
#include "Scenes/colorsScene.h"
#include "Scenes/endRoundscene.h"
#include "Scenes/finalScene.h"
#include "dto_definitions.h"
#include <map>
#include <string>

class GameRenderer {
private:
  Graficos &graficos;
  std::list<ClientDuck> ducks;
  std::list<Bullet> bullets;
  std::list<Gun> guns;
  std::list<Armor> armors;
  std::list<Helmet> helmets;
  std::list<Platform> platforms;
  std::list<Box> boxes;
  static SDL2pp::Rect calcularRectanguloDeZoom(std::list<ClientDuck> &ducks);
  void drawBackground(const uint8_t background_id);

public:
  explicit GameRenderer(Graficos &graficos);
  void dibujar(Renderer &renderer, GameState &command);

  void actualizarElementos(const GameState &command);

  void mostrarPantallaColores(std::map<std::string, std::string> &playersColors,
                              Renderer &renderer);

  void mostrarPantallaEndRound(std::map<std::string, uint8_t> &map_victorias,
                               Renderer &renderer);

  void mostrarPantallaVictoria(std::string &winner, Renderer &renderer);

  ~GameRenderer();
};

#endif // GAMERENDERER_H
