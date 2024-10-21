#include "protocolo.h"

#include <iostream>

Protocolo::Protocolo(Socket& socket_servidor): socket_servidor(socket_servidor) {}

void Protocolo::checkSocketClose(const bool& is_socket_close) {
    if (is_socket_close) {
        throw SocketClose();
    }
}

void Protocolo::sendByte(uint8_t byte, bool& is_socket_close) {
    socket_servidor.sendall(&byte, 1, &is_socket_close);
    checkSocketClose(is_socket_close);
}
void Protocolo::sendShort(uint16_t short_to_send, bool& is_socket_close) {
    uint16_t short_to_send_bg = htons(short_to_send);
    socket_servidor.sendall(&short_to_send_bg, 2, &is_socket_close);
    checkSocketClose(is_socket_close);
}

void Protocolo::sendPlayerName(const std::string& player_name, bool& is_socket_close) {
    uint16_t tam_player_name = htons(player_name.size());
    socket_servidor.sendall(reinterpret_cast<void*>(&tam_player_name), 2, &is_socket_close);
    socket_servidor.sendall(player_name.data(), player_name.size(), &is_socket_close);
    checkSocketClose(is_socket_close);
}


uint8_t Protocolo::receiveByte(bool& is_socket_close) {
    uint8_t byte;
    socket_servidor.recvall(&byte, 1, &is_socket_close);
    return byte;
}


uint16_t Protocolo::receiveShort(bool& is_socket_close) {
    uint16_t short_received;
    socket_servidor.recvall(&short_received, 2, &is_socket_close);
    return ntohs(short_received);
}
std::string Protocolo::receivePlayerName(bool& is_socket_close) {
    uint16_t tam_player_name;
    socket_servidor.recvall(reinterpret_cast<void*>(&tam_player_name), 2, &is_socket_close);
    uint16_t tam_player_name_bg =
            ntohs(tam_player_name);  // the size of the player name in big endian

    // Then I receive the player name
    std::string player_name(tam_player_name_bg, '\0');
    socket_servidor.recvall(player_name.data(), tam_player_name_bg, &is_socket_close);

    return player_name;
}

void Protocolo::sendFloat(float float_to_send, bool& is_socket_close) {
    uint32_t float_to_send_bg = htonl(*reinterpret_cast<uint32_t*>(&float_to_send));
    socket_servidor.sendall(&float_to_send_bg, 4, &is_socket_close);
    checkSocketClose(is_socket_close);
}

float Protocolo::receiveFloat(bool& is_socket_close) {
    uint32_t float_received;
    socket_servidor.recvall(&float_received, 4, &is_socket_close);
    return *reinterpret_cast<float*>(&float_received);
}


Protocolo::~Protocolo() {}
