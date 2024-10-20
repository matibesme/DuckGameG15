#include "protocolo_server.h"

// cppcheck-suppress constParameter
ProtocoloServer::ProtocoloServer(Socket socket, bool& dead_connection) :
    socket_server(std::move(socket)),
    dead_connection(dead_connection),
    protocolo(socket_server) {}

void ProtocoloServer::sendToClient(const CommandGame& command) {
    try {
        if (command.type_of_action == 0x20) {
            sendFullGame(command);
        } else if (command.type_of_action == 0x21) {
            sendEndOfRound(command);
        } else if (command.type_of_action == 0x22) {
            sendVictory(command);
        }
    } catch (const SocketClose& e) {
        std::cerr << "Socket cerrado antes de terminar de enviar" << std::endl;
    } catch (const LibError& e) {
        dead_connection = true;
        std::cerr << e.what() << std::endl;
    }
}

void ProtocoloServer::sendFullGame(const CommandGame& command) {
    protocolo.sendByte(0x20, dead_connection);
    protocolo.sendByte(command.scene_id, dead_connection);
    protocolo.sendByte(command.elements_quantity, dead_connection);
    for (const Element& element : command.elements) {
        protocolo.sendByte(element.element_type, dead_connection);
        protocolo.sendByte(element.element_id, dead_connection);
        protocolo.sendShort(element.x_pos, dead_connection);  // mando uint16 o uint8????
        protocolo.sendShort(element.y_pos, dead_connection);  // mando uint16 o uint8????
        protocolo.sendByte(element.orientation, dead_connection);
    }
}

void ProtocoloServer::sendVictory(const CommandGame& command) {
    protocolo.sendByte(0x22, dead_connection);
    protocolo.sendPlayerName(command.player_name, dead_connection);
}

void ProtocoloServer::sendEndOfRound(const CommandGame& command) {
    protocolo.sendByte(0x21, dead_connection);
    protocolo.sendByte(command.players_quantity, dead_connection);
    for (const PlayerStatus& player : command.players_status) {
        protocolo.sendPlayerName(player.player_name, dead_connection);
        protocolo.sendByte(player.victories, dead_connection);
    }
}

CommandClient ProtocoloServer::receiveCommandFromClients() {
    try {
        uint8_t first_byte = protocolo.receiveByte(dead_connection);
        if (first_byte == 0x09) {}
        // aca me faltaria chequear si estoy recibiendo para setear nivel o movimiento
        uint8_t movement_id = protocolo.receiveByte(dead_connection);
        return {movment_type, movement_id};
    } catch (const LibError& e) {
        dead_connection = true;
        std::cerr << e.what() << std::endl;
    }
    return {"", 0};
}

void ProtocoloServer::closeSocket() {
    try {
        socket_server.shutdown(2);
    } catch (const std::exception& e) {
        // salir de ejecucion
    }
    socket_server.close();
}

ProtocoloServer::~ProtocoloServer() {}
