#ifndef ESPERA_SCENE_H
#define ESPERA_SCENE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>
#include <iostream>

#define FUENTE DATA_PATH "/fonts/8-bit-hud.ttf"

class EsperaScene {
private:
  SDL_Renderer &renderer; // Referencia al renderer
  TTF_Font *font;         // Fuente para el texto

  // Renderizar el mensaje de espera
  void RenderMessage();

public:
  // Constructor que inicializa el renderer y carga la fuente
  explicit EsperaScene(SDL_Renderer &renderer);

  // Destructor que limpia los recursos
  ~EsperaScene();

  // Ejecutar la escena
  void Run();
};

#endif // ESPERA_SCENE_H
