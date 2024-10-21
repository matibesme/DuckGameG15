#include "game_loop.h"


GameLoop::GameLoop(BlockingQueue<CommandGame>& queue_comandos, bool& end_game,
                   ProtectedQueuesMap& queues_map):
        queue_comandos(queue_comandos),
        end_game(end_game),
        queues_map(queues_map),
        personaje() {}

void GameLoop::run() {
    try {
        while (!end_game) {
           
            processCommands();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    } catch (const ClosedQueue& e) {
        // Queue closed
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}


void GameLoop::processCommands() {
    CommandAccess comando;
    while (queue_comandos.try_pop(comando)) {
      
        CommandReward command = {comando.player_name, codigo};
        queues_map.sendMessagesToQueues(command);
    }

}



GameLoop::~GameLoop() {}
