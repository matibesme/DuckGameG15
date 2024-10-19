#pragma once
#include <string>

#include <stdint.h>

const uint8_t FIRST_SEND_BYTE = 0x03;
const uint8_t FIRST_RECIVE_BYTE = 0x06;
const uint8_t NEW_BOX_BYTE = 0x05;
const uint8_t PICKED_UP_BYTE = 0x04;
#define WELCOME_MESSAGE "What is your name?"
#define NEW_BOX_MESSAGE "A new box has appeared"
#define PICKED_UP_MESSAGE " picked up a "
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define CANT_ARGUMENTS 3
#define HOST 1
#define PORT 2
#define EXIT_COMMAND "Exit"
#define READ_COMMAND "Read"
#define PICKUP_COMMAND "Pickup"


// tp final

const uint8_t FULL_GAME_BYTE = 0x20;
const uint8_t END_ROUND_BYTE = 0x21;
const uint8_t VICTORY_BYTE = 0x22;
