#include "sound.h"

// Constructor y destructor
Sound::Sound() {
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    std::cerr << "Error al inicializar SDL_mixer: " << Mix_GetError() << std::endl;
  }
}

Sound::~Sound() {
  limpiar();
}

// Inicialización de SDL_mixer
bool Sound::inicializar() {
  if (Mix_Init(MIX_INIT_MP3) == 0) {
    std::cerr << "Error al inicializar SDL_mixer: " << Mix_GetError() << std::endl;
    return false;
  }
  return true;
}

// Cargar música
void Sound::cargarMusica(const std::string& archivo) {
  musicaFondo = Mix_LoadMUS(archivo.c_str());
  if (!musicaFondo) {
    std::cerr << "Error al cargar música: " << Mix_GetError() << std::endl;
  }
}

// Reproducir música
void Sound::reproducirMusica(int repeticion) {
  if (musicaFondo) {
    Mix_VolumeMusic(1); // Volumen a la mitad
    Mix_PlayMusic(musicaFondo, repeticion);
  } else {
    std::cerr << "No se ha cargado música para reproducir" << std::endl;
  }
}

// Detener música
void Sound::detenerMusica() {
  Mix_HaltMusic();
}

// Cargar efecto de sonido
void Sound::reproducirEfecto(const std::string& archivo) {
  efectoSonido = Mix_LoadWAV(archivo.c_str());
  if (!efectoSonido) {
    std::cerr << "Error al cargar efecto de sonido: " << Mix_GetError() << std::endl;
  }else {
    Mix_VolumeChunk(efectoSonido, 4);
    Mix_PlayChannel(-1, efectoSonido, 0);
  }
}

// Limpiar los recursos de audio
void Sound::limpiar() {
  if (musicaFondo) {
    Mix_FreeMusic(musicaFondo);
    musicaFondo = nullptr;
  }
  if (efectoSonido) {
    Mix_FreeChunk(efectoSonido);
    efectoSonido = nullptr;
  }
  Mix_CloseAudio();
}
