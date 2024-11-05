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

//duck
const int DUCK_WIDTH = 50;
const int DUCK_HEIGHT = 50;

//duck movement actions
const uint8_t MOVEMENT_ACTION = 0x03;
const uint8_t JUMP = 0x04;
const uint8_t RIGTH = 0x05;
const uint8_t LEFT = 0x06;
const uint8_t DOWN = 0x07;
const uint8_t STILL_RIGTH = 0x08;
const uint8_t STILL_LEFT = 0x09;
const uint8_t FLUP = 0x10;
const uint8_t STOP_SHOOT = 0x15;

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
constexpr int HEIGHT_GUN= 20;
constexpr int WIDTH_GUN= 40;
constexpr int HEIGHT_GRENADE_BANANA= 13;
constexpr int WIDTH_GRENADE_BANANA = 15;
constexpr int HEIGHT_GRANADE_EXPLOTION= 60;
constexpr int WIDTH_GRANADE_EXPLOTION= 60;
constexpr uint8_t C_NOGUN= 0X33;
constexpr uint8_t C_COWBOY_GUN= 0X34;
constexpr uint8_t C_COWBOY_BULLET= 0x54;
constexpr uint8_t C_AK47_GUN= 0X35;
constexpr uint8_t C_AK47_BULLET= 0x55;
constexpr uint8_t C_PISTOLA_DUELOS_GUN= 0X36;
constexpr uint8_t C_PISTOLA_DUELOS_BULLET= 0x56;
constexpr uint8_t C_MAGNUM_GUN= 0X37;
constexpr uint8_t C_MAGNUM_BULLET= 0x57;
constexpr uint8_t C_ESCOPETA_GUN= 0X38;
constexpr uint8_t C_ESCOPETA_BULLET= 0x58;
constexpr uint8_t C_SNIPER_GUN= 0X39;
constexpr uint8_t C_SNIPER_BULLET= 0x59;
constexpr uint8_t C_GRANADA_GUN= 0X40;
constexpr uint8_t C_GRANADA_BULLET= 0x60;
constexpr uint8_t C_BANANA_GUN= 0X41;
constexpr uint8_t C_BANANA_BULLET= 0x61;
constexpr uint8_t C_PEW_PEW_LASER_GUN= 0X42;
constexpr uint8_t C_PEW_PEW_LASER_BULLET= 0x62;
constexpr uint8_t C_LASER_RIFLE_GUN= 0X43;
constexpr uint8_t C_LASER_RIFLE_BULLET= 0x63;
constexpr uint8_t C_GRANADA_EXPLOTION= 0x64;

//bullet action
constexpr int HEIGHT_BULLET= 5;
constexpr int WIDTH_BULLET= 5;
const uint8_t BULLET_RIGTH = 0x05;
const uint8_t BULLET_LEFT = 0x06;
const uint8_t BULLET_UP = 0x50;

//armadura completa
const uint8_t C_NOARMOR= 0X73;
const uint8_t C_ARMOR= 0X74;
const uint8_t WIDTH_ARMOR= 60;
const uint8_t HEIGHT_ARMOR= 65;
const uint8_t C_NOHELMET= 0X75;
const uint8_t C_HELMET= 0X76;
const uint8_t WIDTH_HELMET= 60;
const uint8_t HEIGHT_HELMET= 70;

//escena
const uint8_t SCENE = 0x0C;
const int SCENE_WIDTH = 640;
const int SCENE_HEIGHT = 480;



