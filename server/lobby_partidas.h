#include "../common/blocking_queue.h"
#include "../common/dto_definitions.h"
#include "game_loop.h"

class LobbyPartidas {

    private:
        
        
        std::map<uint16_t, GameLoop*> partidas;
        std::map<uint16_t, BlockingQueue<CommandGame>*> map_queues_comandos;
        std::map<uint16_t,ProtectedQueuesMap*> maps_queues_sender;
        uint16_t cantidad_partidas;


    public:
        LobbyPartidas();
        void run();
        void addGame();
        void joinGame(uint16_t id);
        void startGame();
        void deleteGame();
        ~LobbyPartidas();
};
