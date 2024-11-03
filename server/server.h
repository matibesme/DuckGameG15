#include <list>

#include "../common/blocking_queue.h"
#include "../common/dto_definitions.h"
#include "../common/thread.h"

#include "acceptor.h"
#include "server_constant.h"
#include "game_loop.h"
#include "protected_queues_map.h"


class Server {


private:
    bool close;
    ProtectedQueuesMap map_queues_sender;
    BlockingQueue<CommandClient> queue_comandos;
    Acceptor acceptor;
    GameLoop game_loop;


public:
    explicit Server(const char* port);
    void run();
    ~Server();
};
