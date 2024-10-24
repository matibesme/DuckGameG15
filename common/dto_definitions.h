#pragma once
#include <cstdint>
#include <string>
#include <vector>




struct Pato{
    uint8_t personajes_type;
    float x_pos;
    float y_pos;
    uint8_t typeOfMove;//right left down jump still
    uint8_t typeOfGun; // nogun, cowboy ...
};

struct Bala{
    uint8_t element_type; // cowboy Bullet
    float x_pos;
    float y_pos;
    uint8_t orientation; //derecha izquierda
};


struct Armas{ //free wapons in the floor
    float x_pos;
    float y_pos;

};



struct CommandGame {
    uint8_t type_of_action;
    //full game scene
    uint8_t scene_id;

    std::vector<Pato> lista_patos;

    std::vector<Bala> lista_balas;

};



struct CommandGameShow {
    uint8_t scene_id;

    std::vector<Pato> lista_patos;

    std::vector<Bala> lista_balas;

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


