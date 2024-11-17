#include "protocolo_cliente.h"

ProtocoloCliente::ProtocoloCliente(const char *host, const char *port,
                                   bool &dead_connection)
    : socket(host, port), dead_connection(dead_connection), protocolo(socket),
      decode_type_of_action({{RIGHT, MOVEMENT_ACTION},
                             {LEFT, MOVEMENT_ACTION},
                             {JUMP, MOVEMENT_ACTION},
                             {DOWN, MOVEMENT_ACTION},

                             {STILL_LEFT, MOVEMENT_ACTION},
                             {STILL_RIGHT, MOVEMENT_ACTION},
                             {PICKUP, WEAPON_ACTION},
                             {LEAVE_GUN, WEAPON_ACTION},
                             {SHOOT, WEAPON_ACTION},
                             {STOP_SHOOT, WEAPON_ACTION},
                             {AIM_UP, WEAPON_ACTION},
                             {STOP_AIM_UP, WEAPON_ACTION},
                             {CHEAT_CHANGE_WEAPON, WEAPON_ACTION},
                             {CHEAT_STOP_CHANGE_WEAPON, WEAPON_ACTION}}) {}

void ProtocoloCliente::sendInGameToServer(const ClientAction &command) {
  try {
    protocolo.sendByte(decode_type_of_action[command.type_of_movement],
                       dead_connection);
    protocolo.sendByte(command.type_of_movement, dead_connection);
    protocolo.sendByte(command.player, dead_connection);

  } catch (const SocketClose &e) {
    std::cerr << "Socket cerrado antes de terminar de enviar" << std::endl;
  } catch (const std::exception &e) {
    dead_connection = true;
    std::cerr << e.what() << std::endl;
  }
}

GameState ProtocoloCliente::reciveFromServer() {
  try {
    uint8_t firstByte = protocolo.receiveByte(dead_connection);

    if (firstByte == FULL_GAME_BYTE)
      return reciveFullGameFromServer();
    else if (firstByte == END_ROUND_BYTE)
      return reciveEndRoundFromServer();
    else if (firstByte == VICTORY_BYTE)
      return reciveVictoryFromServer();
    else if (firstByte == COLOR_PRESENTATION_BYTE)
      return reciveColorPresentationFromServer();

  } catch (const std::exception &e) {
    dead_connection = true;
    std::cerr << e.what() << std::endl;
  }
  throw ProtocoloError("Error en el protocolo, al recivir mensaje de server");
}

GameState ProtocoloCliente::reciveFullGameFromServer() {

  GameState command;
  command.action = FULL_GAME_BYTE;
  uint8_t background_id = protocolo.receiveByte(dead_connection);
  command.backGround_id = background_id;
  // recivo plataformas
  uint8_t platforms_quantity = protocolo.receiveByte(dead_connection);
  std::list<DTOPlatform> lista_plataformas;
  for (int i = 0; i < platforms_quantity; i++) {
    uint8_t typeOfPlataform = protocolo.receiveByte(dead_connection);
    float x_pos = protocolo.receiveFloat(dead_connection);
    float y_pos = protocolo.receiveFloat(dead_connection);
    float width = protocolo.receiveFloat(dead_connection);
    float height = protocolo.receiveFloat(dead_connection);
    lista_plataformas.push_back({typeOfPlataform, x_pos, y_pos, width, height});
  }
  command.lista_plataformas = lista_plataformas;

  // recivo personajes
  uint8_t patos_quantity = protocolo.receiveByte(dead_connection);
  std::list<DTODuck> lista_patos;
  for (int i = 0; i < patos_quantity; i++) {
    uint8_t id = protocolo.receiveByte(dead_connection);
    std::string personajes_type = protocolo.receiveString(dead_connection);
    float x_pos = protocolo.receiveFloat(dead_connection);
    float y_pos = protocolo.receiveFloat(dead_connection);
    uint8_t typeOfMove = protocolo.receiveByte(dead_connection);
    uint8_t typeOfGun = protocolo.receiveByte(dead_connection);
    uint8_t helmet = protocolo.receiveByte(dead_connection);
    uint8_t armor = protocolo.receiveByte(dead_connection);
    bool is_aiming_up = protocolo.receiveBool(dead_connection);
    uint8_t direction = protocolo.receiveByte(dead_connection);
    lista_patos.push_back({id, personajes_type, x_pos, y_pos, typeOfMove,
                           typeOfGun, helmet, armor, is_aiming_up, direction});
  }

  command.lista_patos = lista_patos;
  // recivo balas
  uint8_t bullets_quantity = protocolo.receiveByte(dead_connection);

  std::list<DTOBullet> bullets;
  for (int i = 0; i < bullets_quantity; i++) {
    uint16_t id = protocolo.receiveShort(dead_connection);
    uint8_t bala_type = protocolo.receiveByte(dead_connection);
    float x_pos = protocolo.receiveFloat(dead_connection);
    float y_pos = protocolo.receiveFloat(dead_connection);
    uint8_t orientation = protocolo.receiveByte(dead_connection);
    bullets.push_back({id, bala_type, x_pos, y_pos, orientation});
  }
  command.lista_balas = bullets;

  // recivo armas libres
  uint8_t guns_quantity = protocolo.receiveByte(dead_connection);
  std::list<DTOGuns> guns;
  for (int i = 0; i < guns_quantity; i++) {
    uint8_t gun_type = protocolo.receiveByte(dead_connection);
    float x_pos = protocolo.receiveFloat(dead_connection);
    float y_pos = protocolo.receiveFloat(dead_connection);
    guns.push_back({gun_type, x_pos, y_pos});
  }
  command.lista_guns = guns;

  std::list<DTOBoxes> lista_boxes;
  uint8_t boxes_quantity = protocolo.receiveByte(dead_connection);
  for (int i = 0; i < boxes_quantity; i++) {
    uint8_t id = protocolo.receiveByte(dead_connection);
    float x_pos = protocolo.receiveFloat(dead_connection);
    float y_pos = protocolo.receiveFloat(dead_connection);
    lista_boxes.push_back({id, x_pos, y_pos});
  }
  command.lista_boxes = lista_boxes;

  uint8_t helmets_quantity = protocolo.receiveByte(dead_connection);
  std::list<Protection> lista_helemets;
  for (int i = 0; i < helmets_quantity; i++) {
    uint8_t type = protocolo.receiveByte(dead_connection);
    float x_pos = protocolo.receiveFloat(dead_connection);
    float y_pos = protocolo.receiveFloat(dead_connection);
    lista_helemets.push_back({type, x_pos, y_pos});
  }
  command.lista_helmets = lista_helemets;

  uint8_t armors_quantity = protocolo.receiveByte(dead_connection);
  std::list<Protection> lista_armors;
  for (int i = 0; i < armors_quantity; i++) {
    uint8_t type = protocolo.receiveByte(dead_connection);
    float x_pos = protocolo.receiveFloat(dead_connection);
    float y_pos = protocolo.receiveFloat(dead_connection);
    lista_armors.push_back({type, x_pos, y_pos});
  }
  command.lista_armors = lista_armors;

  return command;
}

void ProtocoloCliente::sendCreateJoinGameToServer(
    const GameAccess &game_access) {
  try {
    protocolo.sendByte(game_access.action_type, dead_connection);
    protocolo.sendString(game_access.game_name, dead_connection);
    protocolo.sendString(game_access.player1_name, dead_connection);
    protocolo.sendBool(game_access.double_player, dead_connection);
    if (game_access.double_player) {
      protocolo.sendString(game_access.player2_name, dead_connection);
    }
  } catch (const SocketClose &e) {
    std::cerr << "Socket cerrado antes de terminar de enviar" << std::endl;
  } catch (const std::exception &e) {
    dead_connection = true;
    std::cerr << e.what() << std::endl;
  }
}

void ProtocoloCliente::sendRequestGameToServer(const GameAccess &game_access) {
  try {
    protocolo.sendByte(game_access.action_type, dead_connection);
  } catch (const SocketClose &e) {
    std::cerr << "Socket cerrado antes de terminar de enviar" << std::endl;
  } catch (const std::exception &e) {
    dead_connection = true;
    std::cerr << e.what() << std::endl;
  }
}

std::list<std::string> ProtocoloCliente::reciveActiveGamesFromServer() {
  try {
    uint8_t games_quantity = protocolo.receiveByte(dead_connection);

    std::list<std::string> games;
    for (int i = 0; i < games_quantity; i++) {
      std::string game_name = protocolo.receiveString(dead_connection);

      games.push_back(game_name);
    }
    return games;

  } catch (const std::exception &e) {
    dead_connection = true;
    std::cerr << e.what() << std::endl;
  }
  throw ProtocoloError("Error en el protocolo, al recivir mensaje de server");
}

GameState ProtocoloCliente::reciveEndRoundFromServer() {
  try {
    GameState command;
    command.action = END_ROUND_BYTE;
    uint8_t victorias_quantity = protocolo.receiveByte(dead_connection);
    std::map<std::string, uint8_t> lista_victorias;
    for (int i = 0; i < victorias_quantity; i++) {
      std::string id = protocolo.receiveString(dead_connection);
      uint8_t victorias = protocolo.receiveByte(dead_connection);
      lista_victorias.emplace(id, victorias);
    }
    command.map_victorias = lista_victorias;
    return command;
  } catch (const std::exception &e) {
    dead_connection = true;
    std::cerr << e.what() << std::endl;
  }
  throw ProtocoloError("Error en el protocolo, al recivir mensaje de server");
}

GameState ProtocoloCliente::reciveVictoryFromServer() {
  try {
    GameState command;
    command.action = VICTORY_BYTE;
    std::string winner = protocolo.receiveString(dead_connection);
    command.name_winner = winner;

    return command;
  } catch (const std::exception &e) {
    dead_connection = true;
    std::cerr << e.what() << std::endl;
  }
  throw ProtocoloError("Error en el protocolo, al recivir mensaje de server");
}

bool ProtocoloCliente::reciveMatchWithSameName() {
  try {
    return protocolo.receiveBool(dead_connection);
  } catch (const std::exception &e) {
    dead_connection = true;
    std::cerr << e.what() << std::endl;
  }
  throw ProtocoloError("Error en el protocolo, al recivir mensaje de server");
}

GameState ProtocoloCliente::reciveColorPresentationFromServer() {
  try {
    GameState command;
    command.action = COLOR_PRESENTATION_BYTE;
    uint8_t players_quantity = protocolo.receiveByte(dead_connection);
    std::map<std::string, std::string> players_color;
    for (int i = 0; i < players_quantity; i++) {
      std::string player = protocolo.receiveString(dead_connection);
      std::string color = protocolo.receiveString(dead_connection);
      players_color.emplace(player, color);
    }
    command.players_color = players_color;
    return command;
  } catch (const std::exception &e) {
    dead_connection = true;
    std::cerr << e.what() << std::endl;
  }
  throw ProtocoloError("Error en el protocolo, al recivir mensaje de server");
}

ProtocoloCliente::~ProtocoloCliente() {}
