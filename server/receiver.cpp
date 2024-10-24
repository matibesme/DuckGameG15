#include "receiver.h"

//#include "../common/liberror.h"
#include "lobby_partidas.h"

Receiver::Receiver(ProtocoloServer& protocolo, bool& dead_connection,
                   BlockingQueue<CommandClient>& queue_comandos):
        protocolo(protocolo), dead_connection(dead_connection), queue_comandos(queue_comandos) {}

void Receiver::run() {
    try {
        while (!dead_connection) {
            CommandClient command = protocolo.receiveCommandFromClients();
            queue_comandos.push(command);
        }
    } catch (const SocketClose& e) {
        dead_connection = true;
    } catch (const ClosedQueue& e) {
        dead_connection = true;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}


Receiver::~Receiver() = default;
