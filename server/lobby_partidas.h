#include "../common/blocking_queue.h"
#include "../common/dto_definitions.h"


class LobbyPartidas {

    private:
    std::map<uint8_t, std::map<uint8_t,BlockingQueue<CommandGame> >> games_sessions_map;
    
    


    public:
        LobbyPartidas();
        void run();
        ~LobbyPartidas();
};
