#include <list>
#include <utility>

#include "../common/blocking_queue.h"
#include "../common/liberror.h"
#include "../common/socket.h"
#include "../common/thread.h"

#include "protected_queues_map.h"
#include "thread_cliente.h"


class Acceptor: public Thread {

private:
    Socket socket_servidor;
    ProtectedQueuesMap& map_queues_sender;
    std::list<ThreadCliente> lista_clientes;
    BlockingQueue<CommandClient>& queue_comandos;
    bool& close;
    uint8_t cantidad_clientes;


public:
    Acceptor(const char* port, ProtectedQueuesMap& map_queues_sender,
             BlockingQueue<uint8_t>& queue_comandos, bool& close);  //saco el queue_Sender
    virtual void run() override;
    void accept_new_client();
    void deleteAClient(ThreadCliente& cliente);
    void reapDead();
    void closeSocket();

    virtual ~Acceptor();
};
