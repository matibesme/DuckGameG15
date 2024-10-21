#include <exception>
#include <iostream>

#include "client.h"
#include "constant_definitons.h"


int main(int argc, char* argv[]) {
    if (argc != CANT_ARGUMENTS) {
        std::cerr << "Ingrese correctamente la IP o host y el puerto o servicio.\n";
        return EXIT_FAILURE;
    }

    try {
        const char* host = argv[HOST];
        const char* port = argv[PORT];

        Client client(host, port);
        client.execute();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Error desconocido.\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
