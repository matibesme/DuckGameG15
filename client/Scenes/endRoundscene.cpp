#include "endRoundscene.h"
#include <SDL2/SDL_image.h>
#include <iostream>

#define FUENTE DATA_PATH "/fonts/8-bit-hud.ttf"
#define IMAGEN_END_OF_ROUND DATA_PATH "/pantallaColores2.png"

// Modificación: el constructor ahora acepta un renderer como referencia
EndRoundScene::EndRoundScene(std::map<std::string, uint8_t>& players, SDL_Renderer& renderer)
    : players(players), renderer(renderer) {  // Se pasa el renderer al constructor
  // Inicializar SDL
  if (TTF_Init() == -1) {
    std::cerr << "Error al inicializar SDL_ttf: " << TTF_GetError() << std::endl;
    exit(1);
  }

  // Inicializar fuentes (reducido el tamaño de la fuente a 14)
  font = TTF_OpenFont(FUENTE, 14); // Cambié el tamaño de la fuente a 14
  if (!font) {
    std::cerr << "Error al cargar la fuente: " << TTF_GetError() << std::endl;
  }
}

EndRoundScene::~EndRoundScene() {
  // Limpiar recursos
  TTF_CloseFont(font);
  TTF_Quit();
}

void EndRoundScene::RenderBackground() {
  // Renderizar el fondo con una imagen .PNG
  SDL_Surface* background = IMG_Load(IMAGEN_END_OF_ROUND);
  if (!background) {
    std::cerr << "Error al cargar la imagen: " << SDL_GetError() << std::endl;
  }
  SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(&renderer, background);
  SDL_RenderCopy(&renderer, backgroundTexture, NULL, NULL);
  SDL_DestroyTexture(backgroundTexture);
  SDL_FreeSurface(background);
}

void EndRoundScene::RenderTitle() {
  // Renderizar el título con fondo negro
  SDL_Color textColor = {255, 255, 255, 255};  // Blanco
  SDL_Color backgroundColor = {0, 0, 0, 255}; // Fondo negro
  SDL_Surface* textSurface = TTF_RenderText_Blended(font, "End of Round Results", textColor);
  SDL_Texture* textTexture = SDL_CreateTextureFromSurface(&renderer, textSurface);

  // Fondo negro para el texto
  SDL_Rect backgroundRect = { (windowWidth - textSurface->w) / 2 - 10, 20 - 10, textSurface->w + 20, textSurface->h + 20 };
  SDL_SetRenderDrawColor(&renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
  SDL_RenderFillRect(&renderer, &backgroundRect);

  SDL_Rect textRect = { (windowWidth - textSurface->w) / 2, 20, textSurface->w, textSurface->h };
  SDL_RenderCopy(&renderer, textTexture, NULL, &textRect);

  SDL_DestroyTexture(textTexture);
  SDL_FreeSurface(textSurface);
}

void EndRoundScene::RenderResultsTable() {
  // Renderizar los resultados con fondo negro
  int yOffset = 80; // Inicializamos el desplazamiento de y para los resultados
  SDL_Color textColor = {255, 255, 255, 255};  // Blanco
  SDL_Color backgroundColor = {0, 0, 0, 255}; // Fondo negro

  // Ajuste del espaciado para acomodar hasta 6 resultados
  int maxResults = 6;  // Máximo número de resultados a mostrar
  int lineSpacing = 40; // Espaciado entre resultados
  int maxYPosition = yOffset + (maxResults - 1) * lineSpacing; // Ajustar la posición Y del último resultado

  for (const auto& [name, wins] : players) {
    std::string resultText = name + ": " + std::to_string(wins) + " Wins";

    // Renderizar nombre del jugador con fondo negro
    SDL_Surface* nameSurface = TTF_RenderText_Blended(font, resultText.c_str(), textColor);
    SDL_Texture* nameTexture = SDL_CreateTextureFromSurface(&renderer, nameSurface);

    // Fondo negro para los resultados
    SDL_Rect backgroundRect = { (windowWidth - nameSurface->w) / 2 - 10, yOffset - 10, nameSurface->w + 20, nameSurface->h + 20 };
    SDL_SetRenderDrawColor(&renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderFillRect(&renderer, &backgroundRect);

    SDL_Rect nameRect = { (windowWidth - nameSurface->w) / 2, yOffset, nameSurface->w, nameSurface->h };
    SDL_RenderCopy(&renderer, nameTexture, NULL, &nameRect);

    SDL_DestroyTexture(nameTexture);
    SDL_FreeSurface(nameSurface);

    yOffset += lineSpacing;  // Ajustar el desplazamiento para el siguiente resultado

    // Si hemos alcanzado el máximo número de resultados, detener la renderización
    if (yOffset > maxYPosition) {
      break;
    }
  }
}

void EndRoundScene::RenderBorder() {
  // Dibujar borde negro
  SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);  // Negro
  SDL_Rect borderRect = { 0, 0, windowWidth, windowHeight };
  SDL_RenderDrawRect(&renderer, &borderRect);
}

void EndRoundScene::Run() {
  SDL_RenderClear(&renderer);

  RenderBackground();
  RenderTitle();
  RenderResultsTable();
  RenderBorder();

  SDL_RenderPresent(&renderer);

}
