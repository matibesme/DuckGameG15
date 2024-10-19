#include <list>
#include <utility>

#include "../common_src/blocking_queue.h"
#include "../common_src/liberror.h"
#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "protected_queues_map.h"
#include "thread_cliente.h"


class Acceptor: public Thread {

private:
    Socket socket_servidor;
    ProtectedQueuesMap& map_queues_sender;
    std::list<ThreadCliente> lista_clientes;
    BlockingQueue<CommandPickUp>& queue_comandos;
    bool& close;
    uint8_t cantidad_clientes;


public:
    Acceptor(const char* port, ProtectedQueuesMap& map_queues_sender,
             BlockingQueue<CommandPickUp>& queue_comandos, bool& close);
    virtual void run() override;
    void accept_new_client();
    void deleteAClient(ThreadCliente& cliente);
    void reapDead();
    void closeSocket();

    virtual ~Acceptor();
};
