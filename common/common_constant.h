#pragma once
#include <cstdint>
#include <string>

// Estados de salida
// constexpr int EXIT_FAILURE = 1;
// constexpr int EXIT_SUCCESS = 0;

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
constexpr int HEIGHT_BIG_BULLET = 10;
constexpr int WIDTH_BIG_BULLET = 10;
constexpr uint8_t WIDTH_ARMOR = 24;
constexpr uint8_t HEIGHT_ARMOR = 38;
constexpr uint8_t WIDTH_HELMET = 39;
constexpr uint8_t HEIGHT_HELMET = 40;
constexpr int SCENE_WIDTH = 800;
constexpr int SCENE_HEIGHT = 600;
constexpr int MAP_HEIGHT = 64 * DUCK_HEIGHT;
constexpr int MAP_WIDTH = 64 * DUCK_WIDTH;
constexpr int WIDTH_BOX = 17;
constexpr int HEIGHT_BOX = 20;

// Protocolo

// Imagen completa
constexpr uint8_t FULL_GAME_BYTE = 0x20;
constexpr uint8_t END_ROUND_BYTE = 0x21;
constexpr uint8_t VICTORY_BYTE = 0x22;
constexpr uint8_t FINALLY_GAME = 0x23;
constexpr uint8_t COLOR_PRESENTATION_BYTE = 0x24;

// Movimientos del pato
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
constexpr uint8_t ARMOR_EQUIPPED = 0x74;
constexpr uint8_t NO_HELMET = 0x75;
constexpr uint8_t HELMET_EQUIPPED = 0x76;

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

// BOXES
constexpr uint8_t TYPE_BOX = 0X21;
// Constantes adicionales
constexpr char SALIDA = 'q';
constexpr int QUEUE_TAMANIO_MAX = 100;

//  Access to game
constexpr uint8_t JOIN_GAME = 0xCC;
constexpr uint8_t CREATE_GAME = 0xDD;
constexpr uint8_t START_GAME = 0xEE;
constexpr uint8_t LISTAR_PARTIDAS = 0xFF;
constexpr uint8_t MATCH_WITH_SAME_NAME = 0xBB;

// cheat codes
constexpr uint8_t CHEAT_CHANGE_WEAPON = 0x0B;
constexpr uint8_t CHEAT_STOP_CHANGE_WEAPON = 0x0E;
constexpr uint8_t CHEAT_SPAWN_BOX = 0x0C;
constexpr uint8_t CHEAT_SPAWN_ARMOR = 0x0D;
