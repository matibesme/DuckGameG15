#ifndef SONIDOS_H
#define SONIDOS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <iostream>

class Sound {
public:
  Sound();
  ~Sound();

  bool inicializar();
  void cargarMusica(const std::string& archivo);
  void reproducirMusica(int repeticion = -1);  // -1 para repetir indefinidamente
  void detenerMusica();
  void reproducirEfecto(const std::string& archivo);
  void limpiar();

private:
  Mix_Music* musicaFondo = nullptr;
  Mix_Chunk* efectoSonido = nullptr;
};

#endif // SONIDOS_H
