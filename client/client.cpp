#include "client.h"

Client::Client(const char* host, const char* port):
        protocolo(host, port, is_socket_close), is_socket_close(false), decode_id_to_gun() {}

void Client::execute() {
  

    while (!is_socket_close) {
        std::string input;
        std::getline(std::cin, input);

        if (is_socket_close || isExitCommand(input)) {
            is_socket_close = true;
            break;
        }

        int read_times;
        uint8_t box_id;

        if (isReadCommand(input, read_times)) {
            receiveMessages(read_times);
        } else if (isPickUpCommand(input, box_id)) {
            CommandPickUp command = {player_name, box_id};
            protocolo.sendMessegeToServer(command);
        }
    }
}

void Client::firstInteraction() {
    std::cout << WELCOME_MESSAGE << std::endl;
    std::getline(std::cin, player_name);
}

void Client::receiveMessages(int& read_times) {
    while (read_times > 0 && !is_socket_close) {
        try {
            CommandReward command = protocolo.reciveMessegeFromServer();
            if (command.player_name.empty()) {
                std::cout << NEW_BOX_MESSAGE << std::endl;
            } else {
                std::cout << command.player_name << PICKED_UP_MESSAGE
                          << decode_id_to_gun.get_gun(command.reward_id) << std::endl;
            }
            read_times--;
        } catch (const ProtocoloError& e) {
            std::cerr << e.what() << std::endl;
            is_socket_close = true;
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            is_socket_close = true;
        }
    }
}

bool Client::isReadCommand(const std::string& input, int& read_times) {
    std::istringstream iss(input);
    std::string command;
    return (iss >> command >> read_times) && (command == READ_COMMAND);
}

bool Client::isExitCommand(const std::string& input) { return input == EXIT_COMMAND; }

bool Client::isPickUpCommand(const std::string& input, uint8_t& box_id) {
    try {
        std::istringstream iss(input);
        std::string command, box_id_str;
        iss >> command >> box_id_str;
        if (command != PICKUP_COMMAND) {
            return false;
        }
        box_id = std::stoi(box_id_str);
        return true;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    }
    return false;
}

Client::~Client() {}
