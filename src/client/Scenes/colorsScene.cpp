#include "colorsScene.h"
#include <SDL2/SDL_image.h>
#include <iostream>

#define FUENTE DATA_PATH "/fonts/8-bit-hud.ttf"
#define IMAGEN_END_OF_ROUND DATA_PATH "/scenes/pantallaColores.png"

ColorScene::ColorScene(const std::map<std::string, std::string> &playersColors,
                       SDL_Renderer &renderer)
    : playersColors(playersColors), renderer(renderer) {
  // Inicializar SDL_ttf
  if (TTF_Init() == -1) {
    std::cerr << "Error al inicializar SDL_ttf: " << TTF_GetError()
              << std::endl;
    exit(1);
  }

  // Cargar la fuente con un tamaño mayor
  font = TTF_OpenFont(FUENTE, 20); // Tamaño de la fuente aumentado
  if (!font) {
    std::cerr << "Error al cargar la fuente: " << TTF_GetError() << std::endl;
  }
}

ColorScene::~ColorScene() {
  // Limpiar recursos
  TTF_CloseFont(font);
  TTF_Quit();
}

void ColorScene::RenderBackground() {
  // Renderizar el fondo
  SDL_Surface *background = IMG_Load(IMAGEN_END_OF_ROUND);
  if (!background) {
    std::cerr << "Error al cargar la imagen: " << SDL_GetError() << std::endl;
  }
  SDL_Texture *backgroundTexture =
      SDL_CreateTextureFromSurface(&renderer, background);
  SDL_RenderCopy(&renderer, backgroundTexture, NULL, NULL);
  SDL_DestroyTexture(backgroundTexture);
  SDL_FreeSurface(background);
}

void ColorScene::RenderTitle() {
  // Renderizar el título con un fondo negro más estilizado
  SDL_Color textColor = {255, 255, 255, 255}; // Blanco

  SDL_Surface *textSurface =
      TTF_RenderText_Blended(font, "Duck Colors", textColor);
  SDL_Texture *textTexture =
      SDL_CreateTextureFromSurface(&renderer, textSurface);

  SDL_Rect textRect = {(windowWidth - textSurface->w) / 2 - 50, 120,
                       textSurface->w, textSurface->h};
  SDL_RenderCopy(&renderer, textTexture, NULL, &textRect);

  SDL_DestroyTexture(textTexture);
  SDL_FreeSurface(textSurface);
}

void ColorScene::RenderColorTable() {
  // Renderizar la tabla de colores con fuente más grande y fondo negro
  int yOffset = 200;
  SDL_Color textColor = {255, 255, 255, 255}; // Blanco

  for (const auto &[name, color] : playersColors) {
    std::string resultText = name + ": " + color;

    // Renderizar texto del jugador y su color
    SDL_Surface *nameSurface =
        TTF_RenderText_Blended(font, resultText.c_str(), textColor);
    SDL_Texture *nameTexture =
        SDL_CreateTextureFromSurface(&renderer, nameSurface);

    SDL_Rect nameRect = {(windowWidth - nameSurface->w) / 2 - 50, yOffset,
                         nameSurface->w, nameSurface->h};
    SDL_RenderCopy(&renderer, nameTexture, NULL, &nameRect);

    SDL_DestroyTexture(nameTexture);
    SDL_FreeSurface(nameSurface);

    yOffset += 30; // Incrementar el desplazamiento vertical
  }
}

void ColorScene::RenderBorder() {
  // Dibujar borde negro
  SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255); // Negro
  SDL_Rect borderRect = {0, 0, windowWidth, windowHeight};
  SDL_RenderDrawRect(&renderer, &borderRect);
}

void ColorScene::Run() {
  SDL_RenderClear(&renderer);

  RenderBackground();
  RenderTitle();
  RenderColorTable();
  RenderBorder();

  SDL_RenderPresent(&renderer);
}
