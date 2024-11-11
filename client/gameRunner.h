#ifndef GAMERUNNER_H
#define GAMERUNNER_H

#include <list>

#include "Items/Bullet.h"
#include "Items/ClientDuck.h"
#include "common/blocking_queue.h"

#include "EventHandler.h"
#include "GameRenderer.h"
#include "Graficos.h"
#include "sound.h"

class GameRunner {
private:
  Graficos graficos;
  EventHandler handler;
  BlockingQueue<uint8_t> &queue_sender;
  BlockingQueue<GameState> &queue_receiver;
  Sound sound;
  void reproducirMusica();

public:
  GameRunner(BlockingQueue<uint8_t> &queue_sender,
             BlockingQueue<GameState> &queue_receiver);

  void run();

  void delayIfNeeded(std::chrono::high_resolution_clock::time_point &t1,
                     const int delay);
};

#endif // GAMERUNNER_H
