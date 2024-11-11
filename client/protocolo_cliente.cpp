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
                             {STOP_AIM_UP, WEAPON_ACTION}}) {}

void ProtocoloCliente::sendInGameToServer(const uint8_t &command) {
  try {
    protocolo.sendByte(decode_type_of_action[command], dead_connection);
    protocolo.sendByte(command, dead_connection);

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

  } catch (const std::exception &e) {
    dead_connection = true;
    std::cerr << e.what() << std::endl;
  }
  throw ProtocoloError("Error en el protocolo, al recivir mensaje de server");
}

GameState ProtocoloCliente::reciveFullGameFromServer() {
  uint8_t background_id = protocolo.receiveByte(dead_connection);

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

  // recivo armas libres
  uint8_t guns_quantity = protocolo.receiveByte(dead_connection);
  std::list<DTOGuns> guns;
  for (int i = 0; i < guns_quantity; i++) {
    uint8_t gun_type = protocolo.receiveByte(dead_connection);
    float x_pos = protocolo.receiveFloat(dead_connection);
    float y_pos = protocolo.receiveFloat(dead_connection);
    guns.push_back({gun_type, x_pos, y_pos});
  }

  std::list<DTOBoxes> lista_boxes;
  uint8_t boxes_quantity = protocolo.receiveByte(dead_connection);
  for (int i = 0; i < boxes_quantity; i++) {
    uint8_t id = protocolo.receiveByte(dead_connection);
    float x_pos = protocolo.receiveFloat(dead_connection);
    float y_pos = protocolo.receiveFloat(dead_connection);
    lista_boxes.push_back({id, x_pos, y_pos});
  }

  uint8_t helmets_quantity = protocolo.receiveByte(dead_connection);
  std::list<Protection> lista_helemets;
  for (int i = 0; i < helmets_quantity; i++) {
    uint8_t type = protocolo.receiveByte(dead_connection);
    float x_pos = protocolo.receiveFloat(dead_connection);
    float y_pos = protocolo.receiveFloat(dead_connection);
    lista_helemets.push_back({type, x_pos, y_pos});
  }

  uint8_t armors_quantity = protocolo.receiveByte(dead_connection);
  std::list<Protection> lista_armors;
  for (int i = 0; i < armors_quantity; i++) {
    uint8_t type = protocolo.receiveByte(dead_connection);
    float x_pos = protocolo.receiveFloat(dead_connection);
    float y_pos = protocolo.receiveFloat(dead_connection);
    lista_armors.push_back({type, x_pos, y_pos});
  }

  return {background_id, lista_plataformas, lista_patos,    bullets,
          guns,          lista_boxes,       lista_helemets, lista_armors};
}

void ProtocoloCliente::sendAccesToServer(uint8_t action, uint8_t id) {
  try {
    protocolo.sendByte(action, dead_connection);
    protocolo.sendByte(id, dead_connection);
  } catch (const SocketClose &e) {
    std::cerr << "Socket cerrado antes de terminar de enviar" << std::endl;
  } catch (const std::exception &e) {
    dead_connection = true;
    std::cerr << e.what() << std::endl;
  }
}

std::list<uint8_t> ProtocoloCliente::reciveActiveGamesFromServer() {
  try {
    uint8_t firstByte = protocolo.receiveByte(dead_connection);
    if (firstByte == ACTIVE_GAMES_BYTE) {
      uint8_t games_quantity = protocolo.receiveByte(dead_connection);
      std::list<uint8_t> games;
      for (int i = 0; i < games_quantity; i++) {
        uint8_t game_id = protocolo.receiveByte(dead_connection);
        games.push_back(game_id);
      }
      return games;
    }
  } catch (const std::exception &e) {
    dead_connection = true;
    std::cerr << e.what() << std::endl;
  }
  throw ProtocoloError("Error en el protocolo, al recivir mensaje de server");
}

ProtocoloCliente::~ProtocoloCliente() {}