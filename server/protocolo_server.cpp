#include "protocolo_server.h"

// cppcheck-suppress constParameter
ProtocoloServer::ProtocoloServer(Socket socket, bool &dead_connection,
                                 uint8_t id_)
    : socket_server(std::move(socket)), dead_connection(dead_connection),
      protocolo(socket_server), id(id_) {}

void ProtocoloServer::sendToClient(const GameState &command) {
  try {
    if (command.action == FULL_GAME_BYTE)
      sendFullGame(command);
    else if (command.action == END_ROUND_BYTE)
      sendEndRound(command);
    else if (command.action == VICTORY_BYTE)
      sendVictory(command);
    else if (command.action == COLOR_PRESENTATION_BYTE)
      sendPlayersColor(command.players_color);

  } catch (const SocketClose &e) {
    std::cerr << "Socket cerrado antes de terminar de enviar" << std::endl;
  } catch (const std::exception &e) {
    dead_connection = true;
    std::cerr << e.what() << std::endl;
  }
}

void ProtocoloServer::sendFullGame(const GameState &command) {

  protocolo.sendByte(FULL_GAME_BYTE, dead_connection);
  protocolo.sendByte(command.backGround_id, dead_connection);
  protocolo.sendByte(command.lista_plataformas.size(), dead_connection);

  for (const DTOPlatform &dto_platform : command.lista_plataformas) {
    protocolo.sendByte(dto_platform.type, dead_connection);
    protocolo.sendFloat(dto_platform.x_pos, dead_connection);
    protocolo.sendFloat(dto_platform.y_pos, dead_connection);
    protocolo.sendFloat(dto_platform.width, dead_connection);
    protocolo.sendFloat(dto_platform.height, dead_connection);
  }

  // ENVIO DE PERSONAJES

  protocolo.sendByte(command.lista_patos.size(), dead_connection);
  for (const DTODuck &dto_duck : command.lista_patos) {
    protocolo.sendByte(dto_duck.id, dead_connection);
    protocolo.sendString(dto_duck.color, dead_connection);
    protocolo.sendFloat(dto_duck.x_pos, dead_connection);
    protocolo.sendFloat(dto_duck.y_pos, dead_connection);
    protocolo.sendByte(dto_duck.typeOfMove, dead_connection);
    protocolo.sendByte(dto_duck.typeOfGun, dead_connection);
    protocolo.sendByte(dto_duck.helmet, dead_connection);
    protocolo.sendByte(dto_duck.armor, dead_connection);
    protocolo.sendBool(dto_duck.is_aiming_up, dead_connection);
    protocolo.sendByte(dto_duck.direction, dead_connection);
  }

  // ENVIO DE BALAS

  protocolo.sendByte(command.lista_balas.size(), dead_connection);
  for (const DTOBullet &bala : command.lista_balas) {
    protocolo.sendShort(bala.id, dead_connection);
    protocolo.sendByte(bala.typeOfBullet, dead_connection);
    protocolo.sendFloat(bala.x_pos, dead_connection);
    protocolo.sendFloat(bala.y_pos, dead_connection);
    protocolo.sendByte(bala.orientation, dead_connection);
  }

  protocolo.sendByte(command.lista_guns.size(), dead_connection);
  for (const DTOGuns &gun : command.lista_guns) {
    protocolo.sendByte(gun.typeOfGun, dead_connection);
    protocolo.sendFloat(gun.x_pos, dead_connection);
    protocolo.sendFloat(gun.y_pos, dead_connection);
  }

  protocolo.sendByte(command.lista_boxes.size(), dead_connection);
  for (const DTOBoxes &box : command.lista_boxes) {
    protocolo.sendByte(box.id, dead_connection);
    protocolo.sendFloat(box.x_pos, dead_connection);
    protocolo.sendFloat(box.y_pos, dead_connection);
  }

  protocolo.sendByte(command.lista_helmets.size(), dead_connection);
  for (const Protection &helmet : command.lista_helmets) {
    protocolo.sendByte(helmet.type, dead_connection);
    protocolo.sendFloat(helmet.x_pos, dead_connection);
    protocolo.sendFloat(helmet.y_pos, dead_connection);
  }

  protocolo.sendByte(command.lista_armors.size(), dead_connection);
  for (const Protection &armor : command.lista_armors) {
    protocolo.sendByte(armor.type, dead_connection);
    protocolo.sendFloat(armor.x_pos, dead_connection);
    protocolo.sendFloat(armor.y_pos, dead_connection);
  }
}

void ProtocoloServer::sendActiveGames(
    const std::map<std::string, uint8_t> &games) {
  try {

    protocolo.sendByte(games.size(), dead_connection);

    for (const auto &game : games) {
      protocolo.sendString(game.first, dead_connection);
    }
  } catch (const std::exception &e) {
    dead_connection = true;
    std::cerr << e.what() << std::endl;
  }
}

void ProtocoloServer::sendEndRound(const GameState &command) {
  protocolo.sendByte(END_ROUND_BYTE, dead_connection);
  protocolo.sendByte(command.map_victorias.size(), dead_connection);
  for (const auto &victory_round : command.map_victorias) {
    protocolo.sendString(victory_round.first, dead_connection);
    protocolo.sendByte(victory_round.second, dead_connection);
  }
}

void ProtocoloServer::sendVictory(const GameState &command) {
  protocolo.sendByte(VICTORY_BYTE, dead_connection);
  protocolo.sendString(command.name_winner, dead_connection);
}

CommandClient ProtocoloServer::receiveCommandFromClients(bool &two_players) {
  try {
    uint8_t type_of_action = protocolo.receiveByte(dead_connection);
    uint8_t type_of_movement = protocolo.receiveByte(dead_connection);
    uint8_t player = protocolo.receiveByte(dead_connection);
    if (player == 2 && two_players)
      return {type_of_action, type_of_movement, static_cast<uint8_t>(id + 1)};

    return {type_of_action, type_of_movement, id};

  } catch (const std::exception &e) {
    dead_connection = true;
  }
  return {0, 0, 0};
}

GameAccess ProtocoloServer::receiveAccessFromClients() {
  try {
    uint8_t action_type = protocolo.receiveByte(dead_connection);

    if (action_type == LISTAR_PARTIDAS || action_type == START_GAME)
      return {action_type, "", "", false, ""};

    std::string game_name = protocolo.receiveString(dead_connection);
    std::string name = protocolo.receiveString(dead_connection);
    bool double_player = protocolo.receiveBool(dead_connection);
    if (double_player) {
      std::string name2 = protocolo.receiveString(dead_connection);
      return {action_type, game_name, name, double_player, name2};
    }

    return {action_type, game_name, name, false, ""};
  } catch (const std::exception &e) {
    dead_connection = true;
  }
  GameAccess null_access;
  return null_access;
}

void ProtocoloServer::closeSocket() {
  try {
    socket_server.shutdown(2);
  } catch (const std::exception &e) {
    // salir de ejecucion
  }
  socket_server.close();
}

void ProtocoloServer::sendMatchWithSameName(bool same_name) {
  try {
    protocolo.sendBool(same_name, dead_connection);

  } catch (const SocketClose &e) {
    std::cerr << "Socket cerrado antes de terminar de enviar" << std::endl;
  } catch (const std::exception &e) {
    dead_connection = true;
    std::cerr << e.what() << std::endl;
  }
}

void ProtocoloServer::sendPlayersColor(
    const std::map<std::string, std::string> &players_color) {
  try {
    protocolo.sendByte(COLOR_PRESENTATION_BYTE, dead_connection);
    protocolo.sendByte(players_color.size(), dead_connection);
    for (const auto &player : players_color) {
      protocolo.sendString(player.first, dead_connection);
      protocolo.sendString(player.second, dead_connection);
    }
  } catch (const std::exception &e) {
    dead_connection = true;
    std::cerr << e.what() << std::endl;
  }
}

ProtocoloServer::~ProtocoloServer() {}
