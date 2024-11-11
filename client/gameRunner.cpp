#include "gameRunner.h"

#include <chrono>
#include <functional>
#define TITULO "DUCK GAME"
#define SONIDO_FONDO DATA_PATH "/sound/sonidoDeFondo.wav"

GameRunner::GameRunner(BlockingQueue<uint8_t> &queue_sender,
                       BlockingQueue<GameState> &queue_receiver)
    : graficos(TITULO, SCENE_WIDTH, SCENE_HEIGHT), handler(queue_sender),
      queue_sender(queue_sender), queue_receiver(queue_receiver) {}

void GameRunner::run() {
  try {
    graficos.show_window();
    reproducirMusica();

    Renderer &sdl_renderer = graficos.GetRenderer();
    GameState command;
    command = queue_receiver.pop();
    GameRenderer gameRenderer(graficos, command.lista_plataformas,
                              command.lista_boxes);
    gameRenderer.dibujar(sdl_renderer, command);

    bool actualizar = false;
    const int frameDelay = 1000 / 60;

    while (true) {
      auto t1 = std::chrono::high_resolution_clock::now();

      handler.correrHandlers();
      while (queue_receiver.try_pop(command)) // y nos quedamos con la ultima
      {
        actualizar = true;
      }

      if (actualizar) {
        gameRenderer.actualizarElementos(command);
        actualizar = false;
      }
      gameRenderer.dibujar(sdl_renderer, command);

      // llamo al metodo delay para que no se ejecute mas de 60 veces por
      // segundo
      delayIfNeeded(t1, frameDelay);
    }

  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    queue_sender.close();
  }
  graficos.GetRenderer().Clear();
  sound.limpiar();
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

// correr valgrind con
// valgrind --tool=callgrind --compress-strings=no --dump-line=yes
// ./build-relwithdebinfo/tarlike x.xoz a ~/Documents/*pdf en mi caso valgrind
// --tool=callgrind --compress-strings=no
// --dump-line=yes ./taller_client localhost 8080 y luego para ver el callgrind
// kcachegrind callgrind.out.xxxx donde xxxx es el numero de la corrida

// otra app es Linux perf Examples