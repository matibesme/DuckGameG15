#include "protocolo_cliente.h"

ProtocoloCliente::ProtocoloCliente(const char* host, const char* port, bool& dead_connection):
        socket(host, port), dead_connection(dead_connection), protocolo(socket),
        decode_type_of_action({{RIGTH, MOVEMENT_ACTION}, {LEFT, MOVEMENT_ACTION}, {JUMP, MOVEMENT_ACTION}, {DOWN, MOVEMENT_ACTION},{STILL,MOVEMENT_ACTION}, {PICKUP, WEAPON_ACTION}, {LEAVE_GUN, WEAPON_ACTION}, {SHOOT, WEAPON_ACTION}}) {}

/*
void ProtocoloCliente::sendGameAccessToServer(const GameAccess& game_access) {
    try {
        protocolo.sendByte(game_access.action_type);
        protocolo.sendByte(game_access.game_id);
    } catch (const SocketClose& e) {
        std::cerr << "Socket cerrado antes de terminar de enviar" << std::endl;
    } catch (const std::exception& e) {
        dead_connection = true;
        std::cerr << e.what() << std::endl;
    }
}*/

void ProtocoloCliente::sendInGameToServer(const uint8_t& command) {
    try {
        protocolo.sendByte(decode_type_of_action[command],dead_connection);
        protocolo.sendByte(command,dead_connection);

    } catch (const SocketClose& e) {
        std::cerr << "Socket cerrado antes de terminar de enviar" << std::endl;
    } catch (const std::exception& e) {
        dead_connection = true;
        std::cerr << e.what() << std::endl;
    }
}


CommandGameShow ProtocoloCliente::reciveFromServer() {
    try {
        uint8_t firstByte = protocolo.receiveByte(dead_connection);
        if (firstByte==FULL_GAME_BYTE) return reciveFullGameFromServer();
      
    } catch (const std::exception& e) {
        dead_connection = true;
        std::cerr << e.what() << std::endl;
    }
    throw ProtocoloError("Error en el protocolo, al recivir mensaje de server");
}

CommandGameShow ProtocoloCliente::reciveFullGameFromServer() {
    uint8_t scene_id = protocolo.receiveByte(dead_connection);
   
    //recivo personajes
    uint8_t patos_quantity = protocolo.receiveByte(dead_connection);
    std::list<DTODuck> lista_patos;
    for (int i = 0; i < patos_quantity; i++) {
        uint8_t personajes_type = protocolo.receiveByte(dead_connection);
        float x_pos = protocolo.receiveFloat(dead_connection);
        float y_pos = protocolo.receiveFloat(dead_connection);
        uint8_t typeOfMove = protocolo.receiveByte(dead_connection);
        uint8_t typeOfGun = protocolo.receiveByte(dead_connection);
        lista_patos.push_back({personajes_type, x_pos, y_pos, typeOfMove, typeOfGun});
    }
    //recivo balas
    uint8_t bullets_quantity = protocolo.receiveByte(dead_connection);

    std::list<DTOBullet> bullets;
    for (int i = 0; i < bullets_quantity; i++) {
        uint8_t bala_type = protocolo.receiveByte(dead_connection);
        float x_pos = protocolo.receiveFloat(dead_connection);
        float y_pos = protocolo.receiveFloat(dead_connection);
        uint8_t orientation = protocolo.receiveByte(dead_connection);
        bullets.push_back({bala_type, x_pos, y_pos, orientation});
    }

    return {scene_id, lista_patos, bullets};
}
/*
CommandEndOfRound ProtocoloCliente::reciveEndOfRoundFromServer() {
    uint8_t players_quantity = protocolo.receiveByte(dead_connection);
    std::vector<PlayerStatus> players_status;
    for (int i = 0; i < players_quantity; i++) {
        std::string player_name = protocolo.receivePlayerName(dead_connection);
        uint8_t victories = protocolo.receiveByte(dead_connection);
        players_status.push_back({player_name, victories});
    }
    return {players_quantity, players_status};
}

CommandVictory ProtocoloCliente::reciveVictoryFromServer() {
    std::string player_name = protocolo.receivePlayerName(dead_connection);
    return {player_name};
}*/

ProtocoloCliente::~ProtocoloCliente() {}