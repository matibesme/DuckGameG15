#pragma once


constexpr char SALIDA = 'q';
constexpr uint8_t FULL_GAME_BYTE = 0x20;
constexpr uint8_t END_ROUND_BYTE = 0x21;
constexpr uint8_t VICTORY_BYTE = 0x22;
constexpr uint8_t MOVEMENT_ACTION = 0x03;
constexpr uint8_t RIGTH = 0x05;
constexpr uint8_t LEFT = 0x06;
constexpr uint8_t JUMP = 0x04;
constexpr uint8_t DOWN = 0x07;

constexpr uint16_t MOVEMENT_QUANTITY= 0,2;


constexpr uint8_t ORIENTATION_RIGTH = 0x00;
constexpr uint8_t ORIENTATION_LEFT = 0x01;
constexpr uint8_t ORIENTATION_DOWN = 0x02;