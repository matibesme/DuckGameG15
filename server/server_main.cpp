#include <exception>
#include <iostream>

#include "server.h"

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define CANT_ARGUMENTS 2
#define PORT 1


int main(int argc, char* argv[]) {
    if (argc != CANT_ARGUMENTS) {
        std::cerr << "Ingrese unicamente el puerto o servicio donde escucharas la conexión \n";
        return EXIT_FAILURE;
    }

    const char* port = argv[PORT];

    try {

        Server server(port);
        server.run();
    } catch (const std::exception& e) {
        return EXIT_FAILURE;
    } catch (...) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
