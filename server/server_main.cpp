#include <exception>
#include <iostream>

#include "server.h"

#define S_EXIT_FAILURE 1
#define S_EXIT_SUCCESS 0
#define S_CANT_ARGUMENTS 2
#define S_PORT 1


int main(int argc, char* argv[]) {
    if (argc != S_CANT_ARGUMENTS) {
        std::cerr << "Ingrese unicamente el puerto o servicio donde escucharas la conexión \n";
        return S_EXIT_FAILURE;
    }

    const char* port = argv[S_PORT];

    try {

        Server server(port);
        server.run();
    } catch (const std::exception& e) {
        return S_EXIT_FAILURE;
    } catch (...) {
        return S_EXIT_FAILURE;
    }

    return S_EXIT_SUCCESS;
}
