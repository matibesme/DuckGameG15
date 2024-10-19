#include "game_loop.h"


GameLoop::GameLoop(BlockingQueue<CommandPickUp>& queue_comandos, bool& end_game,
                   ProtectedQueuesMap& queues_map):
        queue_comandos(queue_comandos),
        end_game(end_game),
        queues_map(queues_map),
        decode_id_to_gun(),
        boxes_codes({{BAZOOKA_CODE, BAZOOKA},
                     {CHAINSAW_CODE, CHAINSAW},
                     {DEATH_RAY_CODE, DEATH_RAY},
                     {SHOTGUN_CODE, SHOTGUN}}),
        box_times({{BAZOOKA, TIME_BAZOOKA},
                   {CHAINSAW, TIME_CHAINSAW},
                   {DEATH_RAY, TIME_DEATH_RAY},
                   {SHOTGUN, TIME_SHOTGUN}}),
        times_left_to_reappear({{BAZOOKA, TIME_INICIAL},
                                {CHAINSAW, TIME_INICIAL},
                                {DEATH_RAY, TIME_INICIAL},
                                {SHOTGUN, TIME_INICIAL}}) {}

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
    CommandPickUp comando;
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

uint8_t GameLoop::decodeCode(const uint8_t& code) { return boxes_codes.at(code); }

bool GameLoop::isBoxOccupied(const uint8_t& box_id) { return times_left_to_reappear[box_id] > 0; }

bool GameLoop::isNewBoxAppeared() {
    bool new_box_appeared = false;
    for (auto it = times_left_to_reappear.begin(); it != times_left_to_reappear.end(); ++it) {
        if (it->second > 0) {
            it->second--;
            if (it->second == 0) {
                new_box_appeared = true;
            }
        }
    }
    return new_box_appeared;
}

void GameLoop::setBoxOccupied(const uint8_t& box_id) {
    times_left_to_reappear[box_id] = box_times[box_id];
}

GameLoop::~GameLoop() {}
