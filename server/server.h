#include <list>

#include "../common/blocking_queue.h"
#include "../common/dto_definitions.h"
#include "../common/liberror.h"
#include "../common/thread.h"

#include "acceptor.h"
#include "constant_definitons.h"
#include "game_loop.h"
#include "protected_queues_map.h"


class Server {


private:
    bool close;
    ProtectedQueuesMap map_queues_sender;
    BlockingQueue<uint8_t> queue_comandos;
    Acceptor acceptor;
    GameLoop game_loop;


public:
    explicit Server(const char* port);
    void run();
    ~Server();
};
