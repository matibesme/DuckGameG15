#include "game_loop.h"


GameLoop::GameLoop(BlockingQueue<CommandGame>& queue_comandos, bool& end_game,
                   ProtectedQueuesMap& queues_map):
        queue_comandos(queue_comandos),
        end_game(end_game),
        queues_map(queues_map){}

void GameLoop::run() {
    try {
        while (!end_game) {
            handleNewBox();
            processCommands();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    } catch (const ClosedQueue& e) {
        // Queue closed
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void GameLoop::handleNewBox() {
    if (isNewBoxAppeared()) {
        if (end_game)
            return;
        std::cout << "A new box has appeared" << std::endl;
        CommandReward command = {"", 0};
        queues_map.sendMessagesToQueues(command);
    }
}

void GameLoop::processCommands() {
    CommandGame comando;
    while (queue_comandos.try_pop(comando)) {
        uint8_t codigo = decodeCode(comando.box_id);
        if (!isBoxOccupied(codigo)) {
            setBoxOccupied(codigo);
            std::cout << comando.player_name << " picked up a " << decode_id_to_gun.get_gun(codigo)
                      << std::endl;
            CommandReward command = {comando.player_name, codigo};
            queues_map.sendMessagesToQueues(command);
        }
    }
}



GameLoop::~GameLoop() {}
