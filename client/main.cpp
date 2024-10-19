#include "Graficos.h"

#include <iostream>
#include <exception>

int main() try {
    Graficos graficos;
    graficos.iniciar();

	return 0;
} catch (std::exception& e) {
	// If case of error, print it and exit with error
	std::cerr << e.what() << std::endl;
	return 1;
}
