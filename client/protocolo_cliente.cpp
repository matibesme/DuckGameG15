#include "protocolo_cliente.h"

ProtocoloCliente::ProtocoloCliente(const char* host, const char* port, bool& dead_connection):
        socket(host, port), dead_connection(dead_connection), protocolo(socket),
        decode_type_of_action({{RIGTH, MOVEMENT_ACTION}, {LEFT, MOVEMENT_ACTION},
                               {JUMP, MOVEMENT_ACTION}, {DOWN, MOVEMENT_ACTION},
                               {STILL_LEFT,MOVEMENT_ACTION}, {STILL_RIGTH,MOVEMENT_ACTION},
                               {PICKUP, WEAPON_ACTION}, {LEAVE_GUN, WEAPON_ACTION}, {SHOOT, WEAPON_ACTION}}) {}



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
        uint8_t id = protocolo.receiveByte(dead_connection);
        uint8_t personajes_type = protocolo.receiveByte(dead_connection);
        float x_pos = protocolo.receiveFloat(dead_connection);
        float y_pos = protocolo.receiveFloat(dead_connection);
        uint8_t typeOfMove = protocolo.receiveByte(dead_connection);
        uint8_t typeOfGun = protocolo.receiveByte(dead_connection);
        lista_patos.push_back({id,personajes_type, x_pos, y_pos, typeOfMove, typeOfGun});
    }
    //recivo balas
    uint8_t bullets_quantity = protocolo.receiveByte(dead_connection);

    std::list<DTOBullet> bullets;
    for (int i = 0; i < bullets_quantity; i++) {
        uint16_t id = protocolo.receiveShort(dead_connection);
        uint8_t bala_type = protocolo.receiveByte(dead_connection);
        float x_pos = protocolo.receiveFloat(dead_connection);
        float y_pos = protocolo.receiveFloat(dead_connection);
        uint8_t orientation = protocolo.receiveByte(dead_connection);
        bullets.push_back({ id, bala_type, x_pos, y_pos, orientation});
    }

    //recivo armas libres
    uint8_t guns_quantity = protocolo.receiveByte(dead_connection);
    std::list<DTOGuns> guns;
    for (int i = 0; i < guns_quantity; i++) {
        uint8_t gun_type = protocolo.receiveByte(dead_connection);
        float x_pos = protocolo.receiveFloat(dead_connection);
        float y_pos = protocolo.receiveFloat(dead_connection);
        guns.push_back({gun_type, x_pos, y_pos});
    }

    return {scene_id, lista_patos, bullets, guns};
}


ProtocoloCliente::~ProtocoloCliente() {}