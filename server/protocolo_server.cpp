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
  
    protocolo.sendByte(command.personajes.size(), dead_connection);
    for (const Element& element : command.personajes) {
        protocolo.sendFloat(element.x_pos, dead_connection);
        protocolo.sendFloat(element.y_pos, dead_connection);
        protocolo.sendByte(element.typeOfMove, dead_connection);
        protocolo.sendByte(element.typeOfGun, dead_connection);
    }

    //ENVIO DE BALAS
    
    protocolo.sendByte(command.bullets.size(), dead_connection);
    for (const Element& element : command.bullets) {
        protocolo.sendFloat(element.x_pos, dead_connection);
        protocolo.sendFloat(element.y_pos, dead_connection);
        protocolo.sendByte(element.orientation, dead_connection);
    }
}


uint8_t ProtocoloServer::receiveCommandFromClients() {
    try {
    
        uint8_t first_byte = protocolo.receiveByte(dead_connection);
        if (first_byte == S_MOVEMENT_ACTION) {
            return protocolo.receiveByte(dead_connection);
        }
        
        
        

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
