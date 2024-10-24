#pragma once
#include <string>

#include <stdint.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define CANT_ARGUMENTS 3
#define HOST 1
#define PORT 2

//protocolo
const uint8_t FIRST_SEND_BYTE = 0x03;
const uint8_t FIRST_RECIVE_BYTE = 0x06;

//imagen completa
const uint8_t FULL_GAME_BYTE = 0x20;
const uint8_t END_ROUND_BYTE = 0x21;
const uint8_t VICTORY_BYTE = 0x22;

//duck movement actions
const uint8_t MOVEMENT_ACTION = 0x03;
const uint8_t JUMP = 0x04;
const uint8_t RIGTH = 0x05;
const uint8_t LEFT = 0x06;
const uint8_t DOWN = 0x07;
const uint8_t STILL = 0x08;

//escenas
const uint8_t WEAPON_ACTION = 0x08;
const uint8_t PICKUP = 0x09;
const uint8_t LEAVE_GUN= 0x0A;
const uint8_t SHOOT = 0x0B;
const int TAMANIO_MAX = 100;

//posicion inicial del pato
const float POSICION_INICIAL_X = 0.0f;
const float POSICION_INICIAL_Y = 386;

//armas action
constexpr int HEIGHT_GUN= 13;
constexpr int WIDTH_GUN= 25;
constexpr uint8_t C_NOGUN= 0X33;
constexpr uint8_t C_COWBOY_GUN= 0X34;
constexpr uint8_t C_COWBOY_BULLET= 0x54;

//bullet action
constexpr int HEIGHT_BULLET= 5;
constexpr int WIDTH_BULLET= 5;
const uint8_t BULLET_RIGTH = 0x05;
const uint8_t BULLET_LEFT = 0x06;
const uint8_t BULLET_UP = 0x50;


