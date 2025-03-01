#pragma once
#include <cstdint>

// Editor
extern float MAP_LIMIT_X;
extern float MAP_LIMIT_Y;
extern uint8_t SCENE_ID;

// Fisica
extern float GRAVEDAD;
extern float VELOCIDAD_INICIAL;
constexpr float GRAVITY_FLAP = 0.001;
constexpr int CANT_FLAP = 100;

// Pato
extern float POSICION_INICIAL_X;
extern float POSICION_INICIAL_Y;
extern int LIFE;

// Armas en el editor

extern int GRANADA_TIME_TO_EXPLODE;
extern uint8_t COUNTER_TO_SHOOT_GRANADA;
extern float RANGO_X_MEDIO;
extern float RANGO_X_CORTO;
extern float RANGO_X_LARGO;

// GRANADA
extern int DAMAGE_GRANADA;
extern int RANGE_GRANADA;
extern int AMMO_GRANADA;
extern float RECOIL_GRANADA;
extern float RADIO_EXPLOTION_GRANADA;
// BANANA
extern int DAMAGE_BANANA;
extern int RANGE_BANANA;
extern int AMMO_BANANA;
extern float RECOIL_BANANA;
// AK47
extern int DAMAGE_AK47;
extern int RANGE_AK47;
extern int AMMO_AK47;
extern float RECOIL_AK47;
// LASER RIFLE
extern int DAMAGE_LASER_RIFLE;
extern int RANGE_LASER_RIFLE;
extern int AMMO_LASER_RIFLE;
extern float RECOIL_LASER_RIFLE;
// PEW PEW LASER
extern int DAMAGE_PEW_PEW_LASER;
extern int RANGE_PEW_PEW_LASER;
extern int AMMO_PEW_PEW_LASER;
extern float RECOIL_PEW_PEW_LASER;
// ESCOPETA
extern int DAMAGE_ESCOPETA;
extern int RANGE_ESCOPETA;
extern int AMMO_ESCOPETA;
extern float RECOIL_ESCOPETA;
// SNIPER
extern int DAMAGE_SNIPER;
extern int RANGE_SNIPER;
extern int AMMO_SNIPER;
extern float RECOIL_SNIPER;
// COWBOY
extern int DAMAGE_COWBOY;
extern int RANGE_COWBOY;
extern int AMMO_COWBOY;
extern float RECOIL_COWBOY;
// PISTOLA DUELOS
extern int DAMAGE_PISTOLA_DUELOS;
extern int RANGE_PISTOLA_DUELOS;
extern int AMMO_PISTOLA_DUELOS;
extern float RECOIL_PISTOLA_DUELOS;
// MAGNUM
extern int DAMAGE_MAGNUM;
extern int RANGE_MAGNUM;
extern int AMMO_MAGNUM;
extern float RECOIL_MAGNUM;

//
constexpr uint8_t VICTORY_ROUNDS_INICIAL = 0;
extern uint8_t NECESARY_VICTORY_ROUNDS;
extern uint8_t GAMES_PER_ROUND;

constexpr float BULLET_VEL = 8;
constexpr float MOVEMENT_QUANTITY_X = 2;
constexpr float MOVEMENT_QUANTITY_Y = 2;
constexpr float DESPLAZAMIENTO_CON_ARMA_X = 5;
constexpr float MARGEN_DESPLAZAMIENTO_PATO_X = 14;
constexpr float MARGEN_DESPLAZAMIENTO_PATO_X_WALL = 7;
constexpr float MARGEN_DESPLAZAMIENTO_PLATAFORMA_X = 8;
constexpr float MARGEN_DESPLAZAMIENTO_PLATAFORMA_X_IZQ = 12;
constexpr float PLATAFORMA_LEVEMENTE_LEVANTADA = 5;
// TIMES
constexpr int TIME_TO_RESPAWN = 10;
constexpr int START_EXPLOTION = 15;

// Spreads
extern float COWBOY_SPREAD;
extern float AK47_SPREAD_INITIAL;
extern float PISTOLA_DUELOS_SPREAD;
extern float MAGNUM_SPREAD;
extern float ESCOPETA_MAX_SPREAD;
extern float SNIPER_SPREAD;
extern float GRANADA_SPREAD;
extern float BANANA_SPREAD;
extern float PEW_PEW_LASER_MAX_SPREAD;
extern float LASER_RIFLE_SPREAD;

// COnstantes varias
constexpr int CERO = 0;
constexpr int UNO = 1;
constexpr int DOS = 2;
constexpr int TRES = 3;
constexpr int CUATRO = 4;
constexpr int CINCO = 5;
constexpr int SEIS = 6;
constexpr int SIETE = 7;
constexpr int OCHO = 8;
constexpr int NUEVE = 9;
constexpr int DIEZ = 10;
constexpr int VEL_MAX = 15;
constexpr int Y_SPACE = 15;
constexpr int X_SPACE = 1;
constexpr int NULL_VEL = 0;
constexpr float SPREAD_VAR = 0.1;
constexpr float PROBA = 0.5;
constexpr float NO_SPREAD = 0.0;
constexpr int RELOAD_TIME = 70;
constexpr int RESPAWN_TIME = 700;
constexpr int MAX_QUEUE_SIZE = 50;
constexpr int SEND_PRESENTATION_TIME = 1500;
constexpr int VICT_TIME = 150;
constexpr int BOX_HEALTH = 100;
