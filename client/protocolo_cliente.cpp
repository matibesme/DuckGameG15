#include "protocolo_cliente.h"

ProtocoloCliente::ProtocoloCliente(const char* host, const char* port, bool& dead_connection):
        socket(host, port), dead_connection(dead_connection), protocolo(socket) {}

void ProtocoloCliente::sendMessegeToServer(const CommandPickUp& command) {
    try {
        protocolo.sendByte(FIRST_SEND_BYTE, dead_connection);
        protocolo.sendPlayerName(command.player_name, dead_connection);
        protocolo.sendBoxId(command.box_id, dead_connection);
    } catch (const SocketClose& e) {
        std::cerr << "Socket cerrado antes de terminar de enviar" << std::endl;
    } catch (const LibError& e) {
        dead_connection = true;
        std::cerr << e.what() << std::endl;
    }
}

CommandFullGame ProtocoloCliente::reciveFromServer() {
    try {
        uint8_t firstByte = protocolo.receiveByte(dead_connection);
        if (first_byte==FULL_GAME_BYTE) return reciveFullGameFromServer();
        if (firstByte == END_ROUND_BYTE) return reciveEndOfRoundFromServer();
        if (firstByte == VICTORY_BYTE) return reciveVictoryFromServer();
    } catch (const LibError& e) {
        dead_connection = true;
        std::cerr << e.what() << std::endl;
    }
    throw ProtocoloError("Error en el protocolo, al recivir mensaje de server");
}

CommandFullGame ProtocoloCliente::reciveFullGameFromServer() {
    uint8_t scene_id = protocolo.receiveByte(dead_connection);
    uint8_t elements_quantity = protocolo.receiveByte(dead_connection);
    std::vector<Element> elements;
    for (int i = 0; i < elements_quantity; i++) {
        uint8_t element_type = protocolo.receiveByte(dead_connection);
        uint8_t element_id = protocolo.receiveByte(dead_connection);
        uint16_t x_pos = protocolo.receiveShort(dead_connection);
        uint16_t y_pos = protocolo.receiveShort(dead_connection);
        uint8_t orientation = protocolo.receiveByte(dead_connection);
        elements.push_back({element_type, element_id, x_pos, y_pos, orientation});
    }
    return {scene_id, elements_quantity, elements};
}

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
}