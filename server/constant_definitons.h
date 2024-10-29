#pragma once
#include <cstdint>

constexpr char SALIDA = 'q';
//imagen completa
constexpr uint8_t S_FULL_GAME_BYTE = 0x20;
constexpr uint8_t S_END_ROUND_BYTE = 0x21;
constexpr uint8_t S_VICTORY_BYTE = 0x22;


//escenas
constexpr float MAP_LIMIT_X= 640;
constexpr float MAP_LIMIT_Y= 480;
constexpr uint8_t S_SCENE_ID = 0x02;

//movement actions
constexpr uint8_t S_MOVEMENT_ACTION = 0x03;
constexpr uint8_t S_RIGTH = 0x05;
constexpr uint8_t S_LEFT = 0x06;
constexpr uint8_t S_JUMP = 0x04;
constexpr uint8_t S_DOWN = 0x07;
constexpr uint8_t S_STILL_RIGTH = 0x08;
constexpr uint8_t S_STILL_LEFT = 0x09;
constexpr uint8_t S_FLAP = 0x10;
const uint8_t S_UP = 0x50;


constexpr float MOVEMENT_QUANTITY_X= 3;
constexpr float MOVEMENT_QUANTITY_Y= 3;


constexpr uint8_t ORIENTATION_RIGTH = 0x00;
constexpr uint8_t ORIENTATION_LEFT = 0x01;
constexpr uint8_t ORIENTATION_DOWN = 0x02;
constexpr float S_POSICION_INICIAL_X = 0.0f;

//jump
constexpr float S_POSICION_INICIAL_Y = 386;
constexpr float GRAVEDAD = 1;
constexpr float VELOCIDAD_INICIAL = 15;
constexpr float GRAVITY_FLAP = 0.001;
constexpr uint8_t S_CANT_FLAP = 100;


//armas action
const uint8_t S_WEAPON_ACTION = 0x08;
const uint8_t S_PICKUP = 0x09;
const uint8_t S_LEAVE_GUN= 0x0A;
const uint8_t S_SHOOT = 0x0B;

constexpr float BULLET_VEL = 5;
constexpr uint8_t S_NOGUN= 0X33;
constexpr uint8_t S_COWBOY_GUN= 0X34;
constexpr uint8_t S_COWBOY_BULLET= 0x54;
constexpr uint8_t S_AK47_GUN= 0X35;
constexpr uint8_t S_AK47_BULLET= 0x55;
constexpr uint8_t S_PISTOLA_DUELOS_GUN= 0X36;
constexpr uint8_t S_PISTOLA_DUELOS_BULLET= 0x56;
constexpr uint8_t S_MAGNUM_GUN= 0X37;
constexpr uint8_t S_MAGNUM_BULLET= 0x57;
constexpr uint8_t S_ESCOPETA_GUN= 0X38;
constexpr uint8_t S_ESCOPETA_BULLET= 0x58;
constexpr uint8_t S_SNIPER_GUN= 0X39;
constexpr uint8_t S_SNIPER_BULLET= 0x59;
constexpr uint8_t S_GRANADA_GUN= 0X40;
constexpr uint8_t S_GRANADA_BULLET= 0x60;
constexpr uint8_t S_BANANA_GUN= 0X41;
constexpr uint8_t S_BANANA_BULLET= 0x61;
constexpr uint8_t S_PEW_PEW_LASER_GUN= 0X42;
constexpr uint8_t S_PEW_PEW_LASER_BULLET= 0x62;
constexpr uint8_t S_LASER_RIFLE_GUN= 0X43;
constexpr uint8_t S_LASER_RIFLE_BULLET= 0x63;

//duck dimmensions
constexpr int DUCK_WIDTH = 50;
constexpr int DUCK_HEIGHT = 50;


