#include "gameRunner.h"
#include <chrono>
#include <functional>
#define TITULO "DUCK GAME"
#define SONIDO_FONDO DATA_PATH "/sound/sonidoDeFondo.wav"

GameRunner::GameRunner(BlockingQueue<ClientAction> &queue_sender,
                       BlockingQueue<GameState> &queue_receiver)
    : graficos(TITULO, SCENE_WIDTH, SCENE_HEIGHT), handler(queue_sender),
      queue_sender(queue_sender), queue_receiver(queue_receiver) {}

void GameRunner::run() {
  try {
    GameState command;
    graficos.show_window();
    // Muestra la ventana de espera hasta que comience el juego
    GameRenderer::mostrarPantallaDeEspera(graficos.GetRenderer());

    // Crear el renderizador del juego
    GameRenderer gameRenderer(graficos);

    do{
        // Recibir los colores de los jugadores
        command = queue_receiver.pop();
        GameRenderer::mostrarPantallaColores(command.players_color,
                                           graficos.GetRenderer());
    } while (command.action == COLOR_PRESENTATION_BYTE);
    // inició la partida, comienza la música
    reproducirMusica();

    runGameLoop(gameRenderer);
  } catch (const ClosedQueue &e) {
    std::cerr << "Se cerró la cola de mensajes" << std::endl;
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}

void GameRunner::runGameLoop(GameRenderer &gameRenderer) {
  Renderer &sdl_renderer = graficos.GetRenderer();
  bool actualizar = false;
  const int frameDelay = 1000 / 60;
  GameState command;

  while (true) {
    auto t1 = std::chrono::high_resolution_clock::now();

    handler.correrHandlers();

    // Recibimos el comando y actualizamos si es necesario
    while (queue_receiver.try_pop(command)) {
      if (command.action == END_ROUND_BYTE)
        GameRenderer::mostrarPantallaEndRound(command.map_victorias,
                                              sdl_renderer);
      else if (command.action == VICTORY_BYTE)
        GameRenderer::mostrarPantallaVictoria(command.name_winner,
                                              sdl_renderer);
      else if (command.action == FINALLY_GAME)
        throw std::runtime_error("Termino el juego el server");
      else
        actualizar = true;
    }

    if (actualizar) {
      gameRenderer.actualizarElementos(command);
      actualizar = false;
    }

    gameRenderer.dibujar(sdl_renderer, command);

    // Llamamos al método de retraso para asegurar la tasa de 60 FPS
    delayIfNeeded(t1, frameDelay);
  }
}

void GameRunner::delayIfNeeded(
    std::chrono::high_resolution_clock::time_point &t1, const int frameDelay) {
  // Calcular el tiempo de procesamiento de la iteración
  auto t2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float, std::milli> elapsed = t2 - t1;
  int rest = frameDelay - static_cast<int>(elapsed.count());

  // Si estamos retrasados, ajustamos el tiempo de referencia
  if (rest < 0) {
    // Tiempo detrás del programado
    t1 = t2; // Restablece t1 al tiempo actual
  } else {
    // Pausar solo si no estamos retrasados
    std::this_thread::sleep_for(std::chrono::milliseconds(rest));
    t1 += std::chrono::milliseconds(
        frameDelay); // Preparar t1 para la próxima iteración
  }
}

void GameRunner::reproducirMusica() {
  // Inicializar los sonidos
  if (!sound.inicializar()) {
    std::cerr << "Error al inicializar los sonidos" << std::endl;
    return;
  }

  // Cargar música de fondo
  sound.cargarMusica(SONIDO_FONDO);

  // Reproducir la música de fondo
  sound.reproducirMusica(-1); // Repetir indefinidamente
}
