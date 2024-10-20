#include "receiver.h"

#include "../common/liberror.h"

Receiver::Receiver(ProtocoloServer& protocolo, bool& dead_connection,
                   BlockingQueue<CommandGame>& queue_comandos):
        protocolo(protocolo), dead_connection(dead_connection), queue_comandos(queue_comandos) {}

void Receiver::run() {
    try {
        while (!in_game){
            if (protocolo.receiveCommandFromClients().type_of_action == ) {  //aca agrego comando de incio de juego
                in_game = true;
            }
        }


        while (!dead_connection) {

            CommandGame command = protocolo.receiveCommandFromClients();
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
