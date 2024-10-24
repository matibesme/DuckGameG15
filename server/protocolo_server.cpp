#include "protocolo_server.h"

// cppcheck-suppress constParameter
ProtocoloServer::ProtocoloServer(Socket socket, bool& dead_connection) :
    socket_server(std::move(socket)),
    dead_connection(dead_connection),
    protocolo(socket_server) {}

void ProtocoloServer::sendToClient(const CommandGame& command) {
    try {
        if (command.type_of_action == S_FULL_GAME_BYTE) {
            sendFullGame(command);
        }

    } catch (const SocketClose& e) {
        std::cerr << "Socket cerrado antes de terminar de enviar" << std::endl;
    } catch (const std::exception& e) {
        dead_connection = true;
        std::cerr << e.what() << std::endl;
    }
}

void ProtocoloServer::sendFullGame(const CommandGame& command) {
    protocolo.sendByte(S_FULL_GAME_BYTE, dead_connection);
    //ENVIO ESCENA
    protocolo.sendByte(command.scene_id, dead_connection);
    
    //ENVIO DE PERSONAJES
  
    protocolo.sendByte(command.lista_patos.size(), dead_connection);
    for (const DTODuck& dto_duck : command.lista_patos) {
        protocolo.sendFloat(dto_duck.x_pos, dead_connection);
        protocolo.sendFloat(dto_duck.y_pos, dead_connection);
        protocolo.sendByte(dto_duck.typeOfMove, dead_connection);
        protocolo.sendByte(dto_duck.typeOfGun, dead_connection);
    }

    //ENVIO DE BALAS
    
    protocolo.sendByte(command.lista_balas.size(), dead_connection);
    for (const DTOBullet& bala : command.bullets) {
        protocolo.sendFloat(bala.x_pos, dead_connection);
        protocolo.sendFloat(bala.y_pos, dead_connection);
        protocolo.sendByte(bala.orientation, dead_connection);
    }
}


CommandClient ProtocoloServer::receiveCommandFromClients() {
    try {
       
        uint8_t type_of_action = protocolo.receiveByte(dead_connection);
        uint8_t type_of_movement = protocolo.receiveByte(dead_connection);
            
        return {type_of_action, type_of_movement};
        
        
        

    } catch (const std::exception& e) {
        dead_connection = true;
        std::cerr << e.what() << std::endl;
    }
    return 0;
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
