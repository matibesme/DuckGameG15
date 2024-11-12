#pragma once
#include <cstdint>

// Editor
extern float MAP_LIMIT_X;
extern float MAP_LIMIT_Y;
extern uint8_t SCENE_ID;


// Fisica
extern float GRAVEDAD;
extern float VELOCIDAD_INICIAL;
extern float GRAVITY_FLAP;
extern uint8_t CANT_FLAP;

// Pato
extern float POSICION_INICIAL_X;
extern float POSICION_INICIAL_Y;
extern uint8_t LIFE;

// Armas en el editor

extern uint8_t GRANADA_TIME_TO_EXPLODE;
extern uint8_t COUNTER_TO_SHOOT_GRANADA;
extern float RANGO_X_MEDIO;
extern float RANGO_X_CORTO;
extern float RANGO_X_LARGO;

//GRANADA
extern uint8_t DAMAGE_GRANADA;
extern uint8_t RANGE_GRANADA;
extern uint8_t AMMO_GRANADA;
extern float RECOIL_GRANADA;
//BANANA
extern uint8_t DAMAGE_BANANA;
extern uint8_t RANGE_BANANA;
extern uint8_t AMMO_BANANA;
extern float RECOIL_BANANA;
//AK47
extern uint8_t DAMAGE_AK47;
extern uint8_t RANGE_AK47;
extern uint8_t AMMO_AK47;
extern float RECOIL_AK47;
//LASER RIFLE
extern uint8_t DAMAGE_LASER_RIFLE;
extern uint8_t RANGE_LASER_RIFLE;
extern uint8_t AMMO_LASER_RIFLE;
extern float RECOIL_LASER_RIFLE;
//PEW PEW LASER
extern uint8_t DAMAGE_PEW_PEW_LASER;
extern uint8_t RANGE_PEW_PEW_LASER;
extern uint8_t AMMO_PEW_PEW_LASER;
extern float RECOIL_PEW_PEW_LASER;
//ESCOPETA
extern uint8_t DAMAGE_ESCOPETA;
extern uint8_t RANGE_ESCOPETA;
extern uint8_t AMMO_ESCOPETA;
extern float RECOIL_ESCOPETA;
//SNIPER
extern uint8_t DAMAGE_SNIPER;
extern uint8_t RANGE_SNIPER;
extern uint8_t AMMO_SNIPER;
extern float RECOIL_SNIPER;
//COWBOY
extern uint8_t DAMAGE_COWBOY;
extern uint8_t RANGE_COWBOY;
extern uint8_t AMMO_COWBOY;
extern float RECOIL_COWBOY;
//PISTOLA DUELOS
extern uint8_t DAMAGE_PISTOLA_DUELOS;
extern uint8_t RANGE_PISTOLA_DUELOS;
extern uint8_t AMMO_PISTOLA_DUELOS;
extern float RECOIL_PISTOLA_DUELOS;
//MAGNUM
extern uint8_t DAMAGE_MAGNUM;
extern uint8_t RANGE_MAGNUM;
extern uint8_t AMMO_MAGNUM;
extern float RECOIL_MAGNUM;

//
constexpr uint8_t VICTORY_ROUNDS_INICIAL = 0;
constexpr uint8_t NECESARY_VICTORY_ROUNDS = 10;
constexpr uint8_t GAMES_PER_ROUND = 5;

constexpr float BULLET_VEL = 5;
constexpr float MOVEMENT_QUANTITY_X = 3;
constexpr float MOVEMENT_QUANTITY_Y = 3;
//TIMES
constexpr int TIME_TO_RESPAWN = 10;




