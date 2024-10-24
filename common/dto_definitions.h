#pragma once
#include <cstdint>
#include <string>
#include <vector>




struct Personajes{
    uint8_t personajes_type;//the character
    float x_pos;
    float y_pos;
    uint8_t typeOfMove;//right left down jump still
    uint8_t typeOfGun; // nogun, cowboy ...
};

struct Bullet{
    uint8_t element_type; // cowboy Bullet
    float x_pos;
    float y_pos;
    uint8_t orientation; //derecha izquierda
}


struct Weapon{ //free wapons in the floor
    float x_pos;
    float y_pos;    

}



struct CommandGame {
    uint8_t type_of_action;
    //full game scene
    uint8_t scene_id;
    
    std::vector<Personajes> personajes;
    
    std::vector<Bullet> bullets;
    /*
    //end of round scene
    uint8_t players_quantity;
    //std::vector<PlayerStatus> players_status;
    //CommandVictory
    std::string player_name;
    */
};

struct CommandGameShow {
    uint8_t scene_id;
  
    std::vector<Personaje> personajes_list;
  
    std::vector<Bullet> bullets_list;

};


struct CommandClient {
    uint8_t type_of_action; 
    // Movement
    uint8_t type_of_movement;  

    //Weapons
    uint8_t weapon_action;

};

struct GameAccess {
    uint8_t action_type; // new game or join game
    uint8_t game_id;
};


