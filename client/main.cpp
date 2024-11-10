#include <exception>
#include <iostream>
#include <QApplication>

#include "client.h"
#include "../common/common_constant.h"
#include "menu/menucontroller.h"
#include "menu/menu.h"


int main(int argc, char* argv[]) {
    if (argc != CANT_ARGUMENTS) {
        std::cerr << "Ingrese correctamente la IP o host y el puerto o servicio.\n";
        return EXIT_FAILURE;
    }

    try {
        const char* host = argv[HOST];
        const char* port = argv[PORT];

        Client client(host, port);
        MenuController menu_controller(client, argc, argv);
        menu_controller.start_game();
        /*QApplication a(argc, argv);
        Menu w;
        w.show();
        a.exec();*/
        //client.execute();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Error desconocido.\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
