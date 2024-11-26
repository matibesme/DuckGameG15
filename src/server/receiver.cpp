#include "receiver.h"

// #include "../common/liberror.h"

Receiver::Receiver(ProtocoloServer &protocolo, bool &dead_connection,
                   uint8_t id_, LobbyPartidas &lobby)
    : protocolo(protocolo), dead_connection(dead_connection), in_lobby(true),
      start_game(false), queue_comandos(), id(id_), lobby(lobby),
      two_players(false) {}

void Receiver::run() {
  try {
    std::string game_name;
    while (in_lobby && !dead_connection) {
      GameAccess command = protocolo.receiveAccessFromClients();
      if (command.action_type == JOIN_GAME) {
        queue_comandos =
            lobby.joinGame(command.game_name, id, command.player1_name,
                           command.double_player, command.player2_name);
        if (queue_comandos == nullptr) {
          continue;
        }
        in_lobby = false;
        two_players = command.double_player;
        game_name = command.game_name;
      } else if (command.action_type == CREATE_GAME) {
        queue_comandos =
            lobby.addPartida(id, command.player1_name, command.double_player,
                             command.player2_name, command.game_name);
        if (queue_comandos == nullptr) {
          protocolo.sendMatchWithSameName(true);
          continue;
        }
        protocolo.sendMatchWithSameName(false);
        in_lobby = false;
        two_players = command.double_player;
        game_name = command.game_name;
      } else if (command.action_type == LISTAR_PARTIDAS) {
        std::map<std::string, uint8_t> &partidas = lobby.getIdPartidas();
        protocolo.sendActiveGames(partidas);
      }
    }

    if (lobby.isHoster(id)) {
      while (!start_game && !dead_connection) {
        GameAccess command = protocolo.receiveAccessFromClients();
        if (command.action_type == START_GAME) {
          lobby.startGame(id, game_name);
          start_game = true;
        }
      }
    }

    while (!dead_connection) {
      CommandClient command = protocolo.receiveCommandFromClients(two_players);
      queue_comandos->push(command);
    }
  } catch (const SocketClose &e) {
    dead_connection = true;
    std::cerr << "Socket cerreado en el receiver" << std::endl;
  } catch (const ClosedQueue &e) {
    dead_connection = true;
    std::cerr << "Cola cerrada en el receiver" << std::endl;
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}

Receiver::~Receiver() = default;
