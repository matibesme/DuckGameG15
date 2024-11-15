#ifndef FINALSCENE_H
#define FINALSCENE_H

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <string>

class FinalScene {
public:
  // Constructor: recibe el nombre del ganador y el renderer
  FinalScene(std::string winner, SDL_Renderer &renderer);

  // Destructor
  ~FinalScene();

  // Método para renderizar la escena
  void Render();

private:
  std::string winner;             // Nombre del ganador
  SDL_Renderer &renderer;         // Referencia al renderer
  SDL_Texture *backgroundTexture; // Textura del fondo
  TTF_Font *font;                 // Fuente
  std::string message;            // Mensaje a mostrar
};

#endif // FINALSCENE_H
