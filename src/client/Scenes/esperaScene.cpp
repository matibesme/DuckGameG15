#include "esperaScene.h"
#include "common_constant.h"

// Constructor
EsperaScene::EsperaScene(SDL_Renderer &renderer) : renderer(renderer) {
  // Inicializar SDL_ttf
  if (TTF_Init() == -1) {
    std::cerr << "Error al inicializar SDL_ttf: " << TTF_GetError()
              << std::endl;
    exit(1);
  }

  // Cargar fuente
  font = TTF_OpenFont(FUENTE, 20);
  if (!font) {
    std::cerr << "Error al cargar la fuente: " << TTF_GetError() << std::endl;
    exit(1);
  }
}

// Destructor
EsperaScene::~EsperaScene() {
  TTF_CloseFont(font);
  TTF_Quit();
}

void EsperaScene::RenderMessage() {
  // Mensaje dividido en dos renglones
  const char *messageLine1 = "Esperando a que den inicio";
  const char *messageLine2 = "a la partida...";

  // Colores
  SDL_Color textColor = {255, 255, 255, 255}; // Blanco para el texto
  SDL_Color backgroundColor = {0, 0, 0,
                               200}; // Negro semi-transparente para el fondo

  // Renderizar primera línea del texto
  SDL_Surface *line1Surface =
      TTF_RenderText_Blended(font, messageLine1, textColor);
  if (!line1Surface) {
    std::cerr << "Error al renderizar texto: " << TTF_GetError() << std::endl;
    return;
  }
  SDL_Texture *line1Texture =
      SDL_CreateTextureFromSurface(&renderer, line1Surface);
  if (!line1Texture) {
    std::cerr << "Error al crear textura de la línea 1: " << SDL_GetError()
              << std::endl;
    SDL_FreeSurface(line1Surface);
    return;
  }

  // Renderizar segunda línea del texto
  SDL_Surface *line2Surface =
      TTF_RenderText_Blended(font, messageLine2, textColor);
  if (!line2Surface) {
    std::cerr << "Error al renderizar texto: " << TTF_GetError() << std::endl;
    SDL_DestroyTexture(line1Texture);
    SDL_FreeSurface(line1Surface);
    return;
  }
  SDL_Texture *line2Texture =
      SDL_CreateTextureFromSurface(&renderer, line2Surface);
  if (!line2Texture) {
    std::cerr << "Error al crear textura de la línea 2: " << SDL_GetError()
              << std::endl;
    SDL_DestroyTexture(line1Texture);
    SDL_FreeSurface(line1Surface);
    SDL_FreeSurface(line2Surface);
    return;
  }

  // Dimensiones del texto y del fondo
  SDL_Rect line1Rect = {
      (SCENE_WIDTH - line1Surface->w) / 2, // Centrar horizontalmente
      (SCENE_HEIGHT - line1Surface->h) / 2 -
          20, // Centrar verticalmente (ajuste para la primera línea)
      line1Surface->w, line1Surface->h};

  SDL_Rect line2Rect = {
      (SCENE_WIDTH - line2Surface->w) / 2, // Centrar horizontalmente
      (SCENE_HEIGHT - line2Surface->h) / 2 +
          20, // Centrar verticalmente (ajuste para la segunda línea)
      line2Surface->w, line2Surface->h};

  SDL_Rect backgroundRect = {
      std::min(line1Rect.x, line2Rect.x) -
          20,           // Extender el fondo hasta el texto más a la izquierda
      line1Rect.y - 10, // Extender el fondo por encima de la primera línea
      std::max(line1Rect.w, line2Rect.w) +
          40,                        // Extender el ancho al texto más ancho
      line1Rect.h + line2Rect.h + 40 // Altura que cubra ambas líneas y margen
  };

  // Dibujar el fondo semi-transparente
  SDL_SetRenderDrawColor(&renderer, backgroundColor.r, backgroundColor.g,
                         backgroundColor.b, backgroundColor.a);
  SDL_RenderFillRect(&renderer, &backgroundRect);

  // Dibujar las líneas de texto
  SDL_RenderCopy(&renderer, line1Texture, NULL, &line1Rect);
  SDL_RenderCopy(&renderer, line2Texture, NULL, &line2Rect);

  // Limpiar recursos
  SDL_DestroyTexture(line1Texture);
  SDL_DestroyTexture(line2Texture);
  SDL_FreeSurface(line1Surface);
  SDL_FreeSurface(line2Surface);
}

// Ejecutar la escena
void EsperaScene::Run() {
  RenderMessage();
  SDL_RenderPresent(&renderer);
}
