#pragma once


constexpr char SALIDA = 'q';
constexpr uint8_t S_FULL_GAME_BYTE = 0x20;
constexpr uint8_t S_END_ROUND_BYTE = 0x21;
constexpr uint8_t S_VICTORY_BYTE = 0x22;
constexpr uint8_t S_MOVEMENT_ACTION = 0x03;
constexpr uint8_t S_RIGTH = 0x05;
constexpr uint8_t S_LEFT = 0x06;
constexpr uint8_t S_JUMP = 0x04;
constexpr uint8_t S_DOWN = 0x07;
constexpr uint8_t S_STILL = 0x08;

constexpr float MOVEMENT_QUANTITY= 5;
constexpr float MAP_LIMIT_X= 640;
constexpr float MAP_LIMIT_Y= 480;

constexpr float PIXELES_JUMP=150;
constexpr uint8_t ORIENTATION_RIGTH = 0x00;
constexpr uint8_t ORIENTATION_LEFT = 0x01;
constexpr uint8_t ORIENTATION_DOWN = 0x02;