#pragma once
#include <cstdint>
#include <string>
#include <list>

struct DTODuck{
    uint8_t id;
    uint8_t personajes_type;
    float x_pos;
    float y_pos;
    uint8_t typeOfMove;//right left down jump still
    uint8_t typeOfGun; // nogun, cowboy ...
};

struct DTOBullet{
    uint16_t id;
    uint8_t typeOfBullet; // cowboy Bullet
    float x_pos;
    float y_pos;
    uint8_t orientation; //derecha izquierda
};

struct DTOGuns{ //free wapons in the floor
    uint8_t typeOfGun;
    float x_pos;
    float y_pos;
};

struct CommandGame {
    uint8_t scene_id;

    std::list<DTODuck> lista_patos;

    std::list<DTOBullet> lista_balas;

    std::list<DTOGuns> lista_guns;

};

struct CommandClient {
    uint8_t type_of_action; 
    // Movement
    uint8_t type_of_movement;  

};

struct GameAccess {
    uint8_t action_type; // new game or join game
    uint8_t game_id;
};

struct CommandBackGround {
    uint8_t scene_id;

    std::list<DTODuck> lista_patos;

    std::list<DTOBullet> lista_balas;

    std::list<DTOGuns> lista_guns;

};
