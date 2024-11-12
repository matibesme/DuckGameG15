#ifndef ENDROUNDSCENE_H
#define ENDROUNDSCENE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>

class EndRoundScene {
public:
  // Constructor: recibe una referencia a un renderer
  EndRoundScene(std::map<std::string, uint8_t>& players, SDL_Renderer& renderer);

  // Destructor
  ~EndRoundScene();

  // Método para renderizar el fondo
  void RenderBackground();

  // Método para renderizar el título
  void RenderTitle();

  // Método para renderizar la tabla de resultados
  void RenderResultsTable();

  // Método para renderizar el borde
  void RenderBorder();

  // Método principal para ejecutar la escena
  void Run();

private:
  std::map<std::string, uint8_t>& players;  // Referencia al mapa de jugadores y sus victorias
  SDL_Renderer& renderer;  // Referencia al renderer recibido

  // Propiedades de la ventana y la fuente
  TTF_Font* font;
  int windowWidth = 800;
  int windowHeight = 600;
};

#endif // ENDROUNDSCENE_H
