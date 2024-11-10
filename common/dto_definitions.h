#pragma once
#include <cstdint>
#include <string>
#include <list>

struct DTODuck{
    uint8_t id;
    std::string color;
    float x_pos;
    float y_pos;
    uint8_t typeOfMove;//right left down jump still
    uint8_t typeOfGun; // nogun, cowboy ...
    uint8_t helmet;
    uint8_t armor;
    bool is_aiming_up;
    uint8_t direction;
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

struct DTOPlatform{
    uint8_t type;
    float x_pos;
    float y_pos;
    float width;
    float height;
};

struct DTOBoxes{
    uint8_t id;
    float x_pos;
    float y_pos;

};

struct Protection {
    uint8_t type;
    float x_pos;
    float y_pos;
};

struct GameState
{
    uint8_t backGround_id;
    
    std::list<DTOPlatform> lista_plataformas;

    std::list<DTODuck> lista_patos;

    std::list<DTOBullet> lista_balas;

    std::list<DTOGuns> lista_guns;

    std::list<DTOBoxes> lista_boxes;

    std::list<Protection> lista_helmets;

    std::list<Protection> lista_armors;

};

struct CommandClient {
    uint8_t type_of_action; 
    // Movement
    uint8_t type_of_movement;  

};

struct GameAccess {
    uint8_t action_type;
    uint8_t game_id;
   // join game, create game, start game

};



struct CommandBackGround {
    uint8_t background_id;
    std::list<DTOPlatform> lista_plataformas;
};


struct RespawnPoint {
    float x_pos;
    float y_pos;
    uint8_t type;
};



