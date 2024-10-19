#include <list>

#include "../common_src/blocking_queue.h"
#include "../common_src/dto_definitions.h"
#include "../common_src/liberror.h"
#include "../common_src/thread.h"

#include "acceptor.h"
#include "constant_definitons.h"
#include "game_loop.h"
#include "protected_queues_map.h"


class Server {


private:
    bool close;
    ProtectedQueuesMap map_queues_sender;
    BlockingQueue<CommandPickUp> queue_comandos;
    Acceptor acceptor;
    GameLoop game_loop;


public:
    explicit Server(const char* port);
    void run();
    ~Server();
};
