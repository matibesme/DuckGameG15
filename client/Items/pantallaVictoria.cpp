#include "pantallaVictoria.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdexcept>
#include <utility>

#define IMG_VICTORIA DATA_PATH "/pantallaVictoria.png"
#define FONT_PATH DATA_PATH  "/arial.ttf"

PantallaVictoria::PantallaVictoria(std::string name, Graficos& graficos)
    : duckName(std::move(name)), graficos(graficos) {
  draw();
}

void PantallaVictoria::draw() {
  // Cargar la imagen de fondo
  SDL_Surface* surface = IMG_Load(IMG_VICTORIA);
  if (!surface) {
    throw std::runtime_error("Error loading image");
  }

  auto &render = graficos.GetRenderer();
  SDL_Texture* texture = SDL_CreateTextureFromSurface(render.Get(), surface);
  SDL_FreeSurface(surface);  // Liberar superficie ya que la textura ha sido creada

  if (!texture) {
    throw std::runtime_error("Error creating texture");
  }

  // Obtener las dimensiones de la imagen
  int w, h;
  SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

  // Dibujar la imagen de fondo
  SDL_Rect dstrect = {0, 0, w, h};
  SDL_RenderCopy(render.Get(), texture, nullptr, &dstrect);

  // Cargar la fuente
  TTF_Font* font = TTF_OpenFont(FONT_PATH, 10);
  if (!font) {
    SDL_DestroyTexture(texture);
    throw std::runtime_error("Error loading font");
  }

  // Crear el texto "nombre del jugador WIN"
  std::string winText = duckName + " WIN";
  SDL_Color textColor = {255, 255, 255, 255}; // Color blanco para el texto

  SDL_Surface* textSurface = TTF_RenderText_Blended(font, winText.c_str(), textColor);
  if (!textSurface) {
    TTF_CloseFont(font);
    SDL_DestroyTexture(texture);
    throw std::runtime_error("Error creating text surface");
  }

  SDL_Texture* textTexture = SDL_CreateTextureFromSurface(render.Get(), textSurface);
  SDL_FreeSurface(textSurface);  // Liberar superficie ya que la textura ha sido creada

  if (!textTexture) {
    TTF_CloseFont(font);
    SDL_DestroyTexture(texture);
    throw std::runtime_error("Error creating text texture");
  }

  // Definir la posición del texto en la esquina inferior izquierda
  int textW, textH;
  SDL_QueryTexture(textTexture, nullptr, nullptr, &textW, &textH);
  SDL_Rect textRect = {10, h - textH - 10, textW, textH};  // 10 px de margen desde la esquina inferior izquierda

  // Dibujar el texto
  SDL_RenderCopy(render.Get(), textTexture, nullptr, &textRect);
  SDL_RenderPresent(render.Get());

  // Limpiar recursos
  SDL_DestroyTexture(texture);
  SDL_DestroyTexture(textTexture);
  TTF_CloseFont(font);

  // Esperar a que se cierre la ventana
  SDL_Event event;
  while (true) {
    if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
      break;
    }
  }

  SDL_Quit();
}
