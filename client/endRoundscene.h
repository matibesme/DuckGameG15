#ifndef ENDROUNDSCENE_H
#define ENDROUNDSCENE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>

#define FUENTE DATA_PATH "/fonts/8-bit-hud.ttf"
#define IMAGEN_END_OF_ROUND DATA_PATH "/pantallaVictoria.png"

class EndRoundScene {
public:
  EndRoundScene(std::map<std::string, uint8_t>& players);
  ~EndRoundScene();
  void Run();

private:
  void RenderBackground();
  void RenderTitle();
  void RenderResultsTable();
  void RenderBorder();
  SDL_Window* window;
  SDL_Renderer* renderer;
  TTF_Font* font;
  std::map<std::string, uint8_t>& players;
  int windowWidth = 600;
  int windowHeight = 400;
};

#endif // ENDROUNDSCENE_H
