#pragma once
#include "../common/blocking_queue.h"
#include "../common/dto_definitions.h"
#include "game_loop.h"
#include "protected_queues_map.h"
#include <map>
#include <memory>
#include <mutex>

class ThreadCliente;
class LobbyPartidas {

    private:
        uint8_t id_partida;
        std::map<uint8_t, std::unique_ptr<GameLoop>> partidas;
        std::map<uint8_t, std::shared_ptr<ProtectedQueuesMap>> protected_queues_sender;
        std::map<uint8_t, std::shared_ptr<BlockingQueue<GameState>>> queues_sender;
        std::map<uint8_t, std::shared_ptr<BlockingQueue<CommandClient>>> queues_game_loop;
        std::map<uint8_t, uint8_t> id_hoster_partida;
        std::map<uint8_t, bool> end_game;
        std::mutex m;

    public:
        LobbyPartidas();
        std::shared_ptr<BlockingQueue<CommandClient>> addPartida(uint8_t id_cliente);
        void removePartida(uint8_t id_partida);
        std::shared_ptr<BlockingQueue<CommandClient>> joinGame(uint8_t id_partida, uint8_t id_cliente);
        void addQueueSender(uint8_t id_player, std::shared_ptr<BlockingQueue<GameState>> queue);
        bool isHoster(uint8_t id_cliente);
        void startGame(uint8_t id_client);
        void removeQueue(uint8_t id);
        void removeGame(uint8_t id);
        ~LobbyPartidas();
};
