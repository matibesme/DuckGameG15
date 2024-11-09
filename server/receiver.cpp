#include "receiver.h"

//#include "../common/liberror.h"


Receiver::Receiver(ProtocoloServer& protocolo, bool& dead_connection,  uint8_t id_, LobbyPartidas& lobby):
        protocolo(protocolo),
        dead_connection(dead_connection),
        in_lobby(true),
        start_game(false),
        queue_comandos(),
        id(id_),
        lobby(lobby)
        {}

void Receiver::run() {
    try {
        while (in_lobby) {
            GameAccess command = protocolo.receiveAccessFromClients();
            if (command.action_type == JOIN_GAME) {
                queue_comandos = lobby.joinGame(command.game_id, id);
                in_lobby = false;
            } else if (command.action_type == CREATE_GAME) {

                queue_comandos = lobby.addPartida(id);
                in_lobby = false;
            }
        }

        if (lobby.isHoster(id)) {
            while (!start_game)
            {
                GameAccess command = protocolo.receiveAccessFromClients();
                if (command.action_type == START_GAME) {
                    lobby.startGame(id);
                    start_game = true;
                }
            }
        }



        while (!dead_connection) {
            CommandClient command = protocolo.receiveCommandFromClients();
            queue_comandos->push(command);
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
