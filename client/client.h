
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include "../common_src/decode_id_to_gun.h"
#include "../common_src/game_exception.h"

#include "constant_definitons.h"
#include "protocolo_cliente.h"

class Client {
private:
    ProtocoloCliente protocolo;
    bool is_socket_close;
    DecodeIdToGun decode_id_to_gun;
    std::string player_name;

public:
    Client(const char* host, const char* port);
    void execute();           // ciclo de mensajes con el servidor
    void firstInteraction();  // interacción inicial con el usuario
    void sendCommand(const std::string& player_name,
                     const std::string& box_id);  // envia un comando al servidor
    void receiveMessages(int& read_times);        // recibe mensajes del servidor
    bool isReadCommand(const std::string& input, int& read_times);
    bool isExitCommand(const std::string& input);
    bool isPickUpCommand(const std::string& input, uint8_t& box_id);
    ~Client();
};
