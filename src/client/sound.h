#ifndef SONIDOS_H
#define SONIDOS_H

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Sound {
public:
  Sound();
  ~Sound();

  static bool inicializar();
  void cargarMusica(const std::string &archivo);
  void reproducirMusica(int repeticion = -1); // -1 para repetir indefinidamente
  static void ajustarVolumenEfectos();
  void reproducirEfecto(const std::string &archivo);
  void limpiar();

private:
  Mix_Music *musicaFondo = nullptr;
  Mix_Chunk *efectoSonido = nullptr;
};

#endif // SONIDOS_H
