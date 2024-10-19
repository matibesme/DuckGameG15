#pragma once
#include <cstdint>
#include <string>



struct Element{
    uint8_t element_type;
    uint8_t element_id;
    uint16_t x_pos;
    uint16_t y_pos;
    uint8_t orientation;
}

struct PlayerStatus {
    std::string player_name;
    uint8_t victories;
};

struct CommandFullGame {
    uint8_t scene_id;
    uint8_t elements_quantity;
    std::vector<Element> elements;

};

struct CommandVictory {
    std::string player_name;
};

struct CommandEndOfRound {

    uint8_t players_quantity;
    std::vector<PlayerStatus> players_status;
};


struct CommandClient {
    uint8_t type;
    uint8_t command;
};