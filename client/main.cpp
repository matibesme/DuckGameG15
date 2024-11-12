#include <QApplication>
#include <exception>
#include <iostream>

#include "../common/common_constant.h"
#include "menu/menu.h"
#include "menu/menucontroller.h"

#include "client.h"

#include <QApplication>
#include "endRoundscene.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  std::map<uint8_t, std::string> players = {
      {5, "Player1"},
      {3, "Player2"},
      {8, "Player3"}
  };

  EndRoundScene w(players);
  w.show();

  return a.exec();
}


/*
int main(int argc, char *argv[]) {
  if (argc != CANT_ARGUMENTS) {
    std::cerr << "Ingrese correctamente la IP o host y el puerto o servicio.\n";
    return EXIT_FAILURE;
  }

  try {
    const char *host = argv[HOST];
    const char *port = argv[PORT];

    Client client(host, port);
    MenuController menu_controller(client, argc, argv);
    menu_controller.start_game();

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << '\n';
    return EXIT_FAILURE;
  } catch (...) {
    std::cerr << "Error desconocido.\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
*/