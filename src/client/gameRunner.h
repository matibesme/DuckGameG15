#ifndef GAMERUNNER_H
#define GAMERUNNER_H

#include "../common/blocking_queue.h"
#include "EventHandler.h"
#include "GameRenderer.h"
#include "Graficos.h"
#include "Items/Bullet.h"
#include "Items/ClientDuck.h"
#include "sound.h"
#include <list>

class GameRunner {
private:
  Graficos graficos;
  EventHandler handler;
  BlockingQueue<ClientAction> &queue_sender;
  BlockingQueue<GameState> &queue_receiver;
  Sound sound;
  void reproducirMusica();
  void runGameLoop(GameRenderer &gameRenderer);

public:
  GameRunner(BlockingQueue<ClientAction> &queue_sender,
             BlockingQueue<GameState> &queue_receiver);

  void run();

  static void delayIfNeeded(std::chrono::high_resolution_clock::time_point &t1,
                            const int delay);
};

#endif // GAMERUNNER_H
