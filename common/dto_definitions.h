#pragma once
#include <cstdint>
#include <string>



struct Element{
    uint8_t element_type;
    uint8_t element_id;
    uint16_t x_pos;
    uint16_t y_pos;
    uint8_t orientation;
};


struct CommandGame {
    uint8_t type_of_action;

    //full game scene
    uint8_t scene_id;
    uint8_t elements_quantity;
    std::vector<Element> elements;
    //end of round scene
    uint8_t players_quantity;
    std::vector<PlayerStatus> players_status;
    //CommandVictory
    std::string player_name;
};

struct CommandClient {
    uint8_t type_of_action; 
    // Movement
    uint8_t type_of_movement;  

    //Weapons
    uint8_t weapon_action;

}

struct GameAccess {
    uint8_t action_type; // new game or join game
    uint8_t game_id;

    
    
}



struct CommandClient {
    uint8_t type;
    uint8_t command;

};