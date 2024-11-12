#include "receiver.h"

//#include "../common/liberror.h"


Receiver::Receiver(ProtocoloServer& protocolo, bool& dead_connection,  uint8_t id_, LobbyPartidas& lobby):
        protocolo(protocolo),
        dead_connection(dead_connection),
        in_lobby(true),
        start_game(false),
        queue_comandos(),
        id(id_),
        lobby(lobby),
        two_players(false)
        {}

void Receiver::run() {
    try {
        while (in_lobby) {
            GameAccess command = protocolo.receiveAccessFromClients();
            if (command.action_type == JOIN_GAME) {
                queue_comandos = lobby.joinGame(command.game_id, id, command.player1_name, command.double_player, command.player2_name);
                if (queue_comandos == nullptr) {
                    continue;
                }
                in_lobby = false;
                two_players = command.double_player;
            } else if (command.action_type == CREATE_GAME) {

                queue_comandos = lobby.addPartida(id, command.player1_name, command.double_player, command.player2_name);
                in_lobby = false;
                two_players = command.double_player;
            } else if (command.action_type == LISTAR_PARTIDAS) {
               std::map<uint8_t, uint8_t>& partidas = lobby.getIdPartidas();
                protocolo.sendActiveGames(partidas);

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
            CommandClient command = protocolo.receiveCommandFromClients(two_players);
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
