#include "protocolo_server.h"

// cppcheck-suppress constParameter
ProtocoloServer::ProtocoloServer(Socket socket, bool& dead_connection, uint8_t id_):
        socket_server(std::move(socket)),
        dead_connection(dead_connection),
        protocolo(socket_server),
        id(id_) {}

void ProtocoloServer::sendToClient(const GameState& command) {
    try {

        sendFullGame(command);

    } catch (const SocketClose& e) {
        std::cerr << "Socket cerrado antes de terminar de enviar" << std::endl;
    } catch (const std::exception& e) {
        dead_connection = true;
        std::cerr << e.what() << std::endl;
    }
}

void ProtocoloServer::sendFullGame(const GameState& command) {

    protocolo.sendByte(FULL_GAME_BYTE, dead_connection);
    protocolo.sendByte(command.backGround_id, dead_connection);
    protocolo.sendByte(command.lista_plataformas.size(), dead_connection);

    for (const DTOPlatform& dto_platform: command.lista_plataformas) {
        protocolo.sendByte(dto_platform.type, dead_connection);
        protocolo.sendFloat(dto_platform.x_pos, dead_connection);
        protocolo.sendFloat(dto_platform.y_pos, dead_connection);
        protocolo.sendFloat(dto_platform.width, dead_connection);
        protocolo.sendFloat(dto_platform.height, dead_connection);
    }

    // ENVIO DE PERSONAJES

    protocolo.sendByte(command.lista_patos.size(), dead_connection);
    for (const DTODuck& dto_duck: command.lista_patos) {
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
    for (const DTOBullet& bala: command.lista_balas) {
        protocolo.sendShort(bala.id, dead_connection);
        protocolo.sendByte(bala.typeOfBullet, dead_connection);
        protocolo.sendFloat(bala.x_pos, dead_connection);
        protocolo.sendFloat(bala.y_pos, dead_connection);
        protocolo.sendByte(bala.orientation, dead_connection);
    }

    protocolo.sendByte(command.lista_guns.size(), dead_connection);
    for (const DTOGuns& gun: command.lista_guns) {
        protocolo.sendByte(gun.typeOfGun, dead_connection);
        protocolo.sendFloat(gun.x_pos, dead_connection);
        protocolo.sendFloat(gun.y_pos, dead_connection);
    }

    protocolo.sendByte(command.lista_boxes.size(), dead_connection);
    for (const DTOBoxes& box: command.lista_boxes) {
        protocolo.sendByte(box.id, dead_connection);
        protocolo.sendFloat(box.x_pos, dead_connection);
        protocolo.sendFloat(box.y_pos, dead_connection);
    }

    protocolo.sendByte(command.lista_helmets.size(), dead_connection);
    for (const Protection& helmet: command.lista_helmets) {
        protocolo.sendByte(helmet.type, dead_connection);
        protocolo.sendFloat(helmet.x_pos, dead_connection);
        protocolo.sendFloat(helmet.y_pos, dead_connection);
    }

    protocolo.sendByte(command.lista_armors.size(), dead_connection);
    for (const Protection& armor: command.lista_armors) {
        protocolo.sendByte(armor.type, dead_connection);
        protocolo.sendFloat(armor.x_pos, dead_connection);
        protocolo.sendFloat(armor.y_pos, dead_connection);
    }
}

void ProtocoloServer::sendActiveGames(const std::map<uint8_t, uint8_t>& games) {
    try {
        protocolo.sendByte(ACTIVE_GAMES_BYTE, dead_connection);
        protocolo.sendByte(games.size(), dead_connection);
        for (const auto& game: games) {
            protocolo.sendByte(game.first, dead_connection);
        }
    } catch (const std::exception& e) {
        dead_connection = true;
        std::cerr << e.what() << std::endl;
    }
}


CommandClient ProtocoloServer::receiveCommandFromClients() {
    try {

        uint8_t type_of_action = protocolo.receiveByte(dead_connection);
        uint8_t type_of_movement = protocolo.receiveByte(dead_connection);
        return {type_of_action, type_of_movement, id};

    } catch (const std::exception& e) {
        dead_connection = true;
        std::cerr << e.what() << std::endl;
    }
    return {0, 0, 0};
}

GameAccess ProtocoloServer::receiveAccessFromClients() {
    try {
        uint8_t action_type = protocolo.receiveByte(dead_connection);
        uint8_t game_id = protocolo.receiveByte(dead_connection);
        return {action_type, game_id};
    } catch (const std::exception& e) {
        dead_connection = true;
        std::cerr << e.what() << std::endl;
    }
    return {0, 0};
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
