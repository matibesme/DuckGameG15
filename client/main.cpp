#include "Game.h"

#include <iostream>
#include <exception>

int main() try {
    Game game;
    game.run();

	return 0;
} catch (std::exception& e) {
	// If case of error, print it and exit with error
	std::cerr << e.what() << std::endl;
	return 1;
}
