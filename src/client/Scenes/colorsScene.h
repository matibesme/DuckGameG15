#ifndef COLORSCENE_H
#define COLORSCENE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>

class ColorScene {
public:
  // Constructor: recibe un mapa de jugadores a colores y un renderer
  ColorScene(const std::map<std::string, std::string> &playersColors,
             SDL_Renderer &renderer);

  // Destructor
  ~ColorScene();

  // Método principal para ejecutar la escena
  void Run();

private:
  const std::map<std::string, std::string>
      &playersColors;     // Referencia al mapa de jugadores y colores
  SDL_Renderer &renderer; // Referencia al renderer recibido

  // Propiedades de la ventana y la fuente
  TTF_Font *font;
  int windowWidth = 800;
  int windowHeight = 600;

  // Métodos internos
  void RenderBackground();
  void RenderTitle();
  void RenderColorTable();
  void RenderBorder();
};

#endif // COLORSCENE_H
