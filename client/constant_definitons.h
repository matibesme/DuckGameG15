#pragma once
#include <string>

#include <stdint.h>

const uint8_t FIRST_SEND_BYTE = 0x03;
const uint8_t FIRST_RECIVE_BYTE = 0x06;

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define CANT_ARGUMENTS 3
#define HOST 1
#define PORT 2

const uint8_t FULL_GAME_BYTE = 0x20;
const uint8_t END_ROUND_BYTE = 0x21;
const uint8_t VICTORY_BYTE = 0x22;

const uint8_t MOVEMENT_ACTION = 0x03;

const uint8_t JUMP = 0x04;
const uint8_t RIGTH = 0x05;
const uint8_t LEFT = 0x06;
const uint8_t DOWN = 0x07;
const uint8_t STILL = 0x08;


const uint8_t WEAPON_ACTION = 0x08;
const uint8_t PICKUP = 0x09;
const uint8_t LEAVE_GUN= 0x0A;
const uint8_t SHOT = 0x0B;
const uint8_t AIM_UP = 0x0C;
const int TAMANIO_MAX = 100;

const float POSICION_INICIAL_X = 0.0f;
const float POSICION_INICIAL_Y = 386;
