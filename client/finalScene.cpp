#include "finalScene.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

#define IMAGEN_VICTORIA DATA_PATH "/pantallaVictoria.png"
#define FUENTE DATA_PATH "/fonts/8-bit-hud.ttf"

FinalScene::FinalScene(std::string winner, SDL_Renderer& renderer)
    : winner(winner), renderer(renderer) {
  // Inicializar SDL_ttf
  if (TTF_Init() == -1) {
    std::cerr << "Error al inicializar SDL_ttf: " << TTF_GetError() << std::endl;
    exit(1);
  }

  // Cargar la imagen de fondo
  SDL_Surface* background = IMG_Load(IMAGEN_VICTORIA);
  if (!background) {
    std::cerr << "Error al cargar la imagen: " << SDL_GetError() << std::endl;
  }
  backgroundTexture = SDL_CreateTextureFromSurface(&renderer, background);
  SDL_FreeSurface(background);

  // Cargar la fuente
  font = TTF_OpenFont(FUENTE, 24);  // Tamaño de fuente
  if (!font) {
    std::cerr << "Error al cargar la fuente: " << TTF_GetError() << std::endl;
  }

  // Mensaje del ganador
  message = "Winner is " + winner;
}

FinalScene::~FinalScene() {
  // Limpiar recursos
  SDL_DestroyTexture(backgroundTexture);
  TTF_CloseFont(font);
  TTF_Quit();
}

void FinalScene::Render() {
  // Renderizar el fondo
  SDL_RenderCopy(&renderer, backgroundTexture, NULL, NULL);

  // Renderizar el mensaje del ganador con fondo negro
  SDL_Color textColor = {255, 255, 255, 255};  // Blanco
  SDL_Surface* textSurface = TTF_RenderText_Blended(font, message.c_str(), textColor);

  // Crear un fondo negro para el texto
  SDL_Rect textRect = { 50, 400, textSurface->w, textSurface->h };
  SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);  // Negro
  SDL_RenderFillRect(&renderer, &textRect);  // Dibujar el rectángulo negro detrás del texto

  // Renderizar el texto
  SDL_Texture* textTexture = SDL_CreateTextureFromSurface(&renderer, textSurface);
  SDL_RenderCopy(&renderer, textTexture, NULL, &textRect);

  SDL_DestroyTexture(textTexture);
  SDL_FreeSurface(textSurface);
  // Actualizar la pantalla
  SDL_RenderPresent(&renderer);
}

