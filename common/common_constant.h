#pragma once
#include <cstdint>
#include <string>

// Estados de salida
//constexpr int EXIT_FAILURE = 1;
//constexpr int EXIT_SUCCESS = 0;

// Argumentos y configuración de red
constexpr int CANT_ARGUMENTS = 3;
constexpr int HOST = 1;
constexpr int PORT = 2;

// Tamaños
constexpr int DUCK_WIDTH = 32;
constexpr int DUCK_HEIGHT = 32;
constexpr int HEIGHT_GUN = 9;
constexpr int WIDTH_GUN = 15;
constexpr int HEIGHT_GRENADE_BANANA = 13;
constexpr int WIDTH_GRENADE_BANANA = 15;
constexpr int HEIGHT_GRENADE_EXPLOTION = 40;
constexpr int WIDTH_GRENADE_EXPLOTION = 40;
constexpr int HEIGHT_BULLET = 3;
constexpr int WIDTH_BULLET = 3;
constexpr uint8_t WIDTH_ARMOR = 27;
constexpr uint8_t HEIGHT_ARMOR = 42;
constexpr uint8_t WIDTH_HELMET = 39;
constexpr uint8_t HEIGHT_HELMET = 40;
constexpr int SCENE_WIDTH = 800;
constexpr int SCENE_HEIGHT = 600;
constexpr int MAP_HEIGHT = 64 * DUCK_HEIGHT;
constexpr int MAP_WIDTH = 64 * DUCK_WIDTH;
constexpr int WIDTH_BOX = 32;
constexpr int HEIGHT_BOX = 32;

// Protocolo
constexpr uint8_t FIRST_SEND_BYTE = 0x03;
constexpr uint8_t FIRST_RECEIVE_BYTE = 0x06;

// Imagen completa
constexpr uint8_t BACKGROUND_BYTE = 0x19;
constexpr uint8_t FULL_GAME_BYTE = 0x20;
constexpr uint8_t END_ROUND_BYTE = 0x21;
constexpr uint8_t VICTORY_BYTE = 0x22;

// Movimientos del pato 1
constexpr uint8_t MOVEMENT_ACTION = 0x03;
constexpr uint8_t JUMP = 0x04;
constexpr uint8_t RIGHT = 0x05;
constexpr uint8_t LEFT = 0x06;
constexpr uint8_t DOWN = 0x07;
constexpr uint8_t STILL_RIGHT = 0x08;
constexpr uint8_t STILL_LEFT = 0x09;
constexpr uint8_t FLAP = 0x10;
constexpr uint8_t SHOOT = 0x11;
constexpr uint8_t PICKUP = 0x12;
constexpr uint8_t AIM_UP = 0x13;
constexpr uint8_t STOP_AIM_UP = 0x14;
constexpr uint8_t STOP_SHOOT = 0x15;
constexpr uint8_t LEAVE_GUN = 0x0A;

// Movimientos del pato 2
constexpr uint8_t JUMP_J2 = 0x17;
constexpr uint8_t RIGHT_J2 = 0x18;
constexpr uint8_t LEFT_J2 = 0x19;
constexpr uint8_t DOWN_J2 = 0x20;
constexpr uint8_t STILL_RIGHT_J2 = 0x21;
constexpr uint8_t STILL_LEFT_J2 = 0x22;
constexpr uint8_t FLAP_J2 = 0x23;
constexpr uint8_t SHOOT_J2 = 0x24;
constexpr uint8_t PICKUP_J2 = 0x25;
constexpr uint8_t AIM_UP_J2 = 0x26;
constexpr uint8_t STOP_AIM_UP_J2 = 0x27;
constexpr uint8_t STOP_SHOOT_J2 = 0x28;
constexpr uint8_t LEAVE_GUN_J2 = 0x29;

// Escenas
constexpr uint8_t WEAPON_ACTION = 0x08;
constexpr uint8_t SCENE = 0x0C;

// Orientación de balas
constexpr uint8_t BULLET_RIGHT = 0x05;
constexpr uint8_t BULLET_LEFT = 0x06;
constexpr uint8_t BULLET_UP = 0x50;

// Orientaciones adicionales
constexpr uint8_t ORIENTATION_RIGHT = 0x00;
constexpr uint8_t ORIENTATION_LEFT = 0x01;
constexpr uint8_t ORIENTATION_DOWN = 0x02;

// Acciones de armas
constexpr uint8_t NOGUN = 0x33;
constexpr uint8_t COWBOY_GUN = 0x34;
constexpr uint8_t COWBOY_BULLET = 0x54;
constexpr uint8_t AK47_GUN = 0x35;
constexpr uint8_t AK47_BULLET = 0x55;
constexpr uint8_t PISTOLA_DUELOS_GUN = 0x36;
constexpr uint8_t PISTOLA_DUELOS_BULLET = 0x56;
constexpr uint8_t MAGNUM_GUN = 0x37;
constexpr uint8_t MAGNUM_BULLET = 0x57;
constexpr uint8_t ESCOPETA_GUN = 0x38;
constexpr uint8_t ESCOPETA_BULLET = 0x58;
constexpr uint8_t SNIPER_GUN = 0x39;
constexpr uint8_t SNIPER_BULLET = 0x59;
constexpr uint8_t GRANADA_GUN = 0x40;
constexpr uint8_t GRANADA_BULLET = 0x60;
constexpr uint8_t BANANA_GUN = 0x41;
constexpr uint8_t BANANA_BULLET = 0x61;
constexpr uint8_t PEW_PEW_LASER_GUN = 0x42;
constexpr uint8_t PEW_PEW_LASER_BULLET = 0x62;
constexpr uint8_t LASER_RIFLE_GUN = 0x43;
constexpr uint8_t LASER_RIFLE_BULLET = 0x63;
constexpr uint8_t GRENADE_EXPLOSION = 0x64;

// Armadura completa
constexpr uint8_t NO_ARMOR = 0x73;
constexpr uint8_t ARMOR = 0x74;
constexpr uint8_t NO_HELMET = 0x75;
constexpr uint8_t HELMET = 0x76;

// Plataformas
constexpr uint8_t TYPE_PLATFORM_DONUT = 0x77;
constexpr uint8_t TYPE_PLATFORM_INDUSTRIAL = 0x78;
constexpr uint8_t TYPE_PLATFORM_NATURE = 0x79;
constexpr uint8_t TYPE_PLATFORM_SPACE = 0x80;
constexpr uint8_t TYPE_PLATFORM_UNDERGROUND = 0x81;
constexpr uint8_t TYPE_PLATFORM_DONUT_LONG = 0x82;
constexpr uint8_t TYPE_PLATFORM_NATURE_LONG = 0x83;


// Walls
constexpr uint8_t TYPE_WALL_DONUT = 0x85;
constexpr uint8_t TYPE_WALL_NATURE = 0x86;
constexpr uint8_t TYPE_WALL_UNDERGROUND = 0X87;

// Backgrounds
constexpr uint8_t TYPE_BACKGROUND_CITY = 0x90;
constexpr uint8_t TYPE_BACKGROUND_FOREST = 0x91;
constexpr uint8_t TYPE_BACKGROUND_CIELO_NUBES = 0x92;

// Constantes adicionales
constexpr char SALIDA = 'q';
constexpr int QUEUE_TAMANIO_MAX = 100;
constexpr float BULLET_VEL = 5;
constexpr float MOVEMENT_QUANTITY_X = 3;
constexpr float MOVEMENT_QUANTITY_Y = 3;


//  Access to game
constexpr uint8_t JOIN_GAME = 0xCC;
constexpr uint8_t CREATE_GAME = 0xDD;
constexpr uint8_t START_GAME = 0xEE;