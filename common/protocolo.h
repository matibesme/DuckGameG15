#pragma once
#include <cstdint>
#include <string>

#include <arpa/inet.h>

#include "../common/game_exception.h"
#include "../common/socket.h"


class Protocolo {
private:
    Socket& socket_servidor;

public:
    explicit Protocolo(Socket& socket_servidor);

    void checkSocketClose(const bool& is_socket_close);
    void sendByte(uint8_t byte, bool& is_socket_close);
    void sendPlayerName(const std::string& player_name, bool& is_socket_close);
    void sendShort(uint16_t short_to_send, bool& is_socket_close);
    uint16_t receiveShort(bool& is_socket_close);
    uint8_t receiveByte(bool& is_socket_close);
    std::string receivePlayerName(bool& is_socket_close);
    void sendFloat(float float_to_send, bool& is_socket_close);
    float receiveFloat(bool& is_socket_close);


    ~Protocolo();
};
