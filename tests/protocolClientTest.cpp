#include "gtest/gtest.h"
#include "protocolo_cliente.h"
#include "game_exception.h"
#include "../common/socket.h"
#include <iostream>

int main() {
  // Simulando una conexión
  bool dead_connection = false;
  ProtocoloCliente cliente("localhost", "8080", dead_connection);

  // Creando un objeto de acción de cliente
  ClientAction accion;
  accion.type_of_movement = RIGHT;
  accion.player = 1;
  accion.type_of_movement = MOVEMENT_ACTION;

  std::cout << "Enviando acción al servidor..." << std::endl;
  cliente.sendInGameToServer(accion);

  // Recibiendo estado del juego
  std::cout << "Recibiendo estado del juego..." << std::endl;
  try {
    GameState estado = cliente.reciveFromServer();
    std::cout << "Estado del juego recibido. Acción: " << static_cast<int>(estado.action) << std::endl;

    if (estado.action == FULL_GAME_BYTE) {
      std::cout << "Juego completo recibido" << std::endl;
    } else if (estado.action == END_ROUND_BYTE) {
      std::cout << "Fin de ronda recibido" << std::endl;
    }
  } catch (const ProtocoloError &e) {
    std::cerr << "Error en la recepción: " << e.what() << std::endl;
  }

  // Enviando creación de juego al servidor
  GameAccess game_access = {CREATE_GAME, "Game1", "Player1", false, ""};
  cliente.sendCreateJoinGameToServer(game_access);

  // Recibiendo juego activo del servidor
  try {
    std::list<std::string> juegos = cliente.reciveActiveGamesFromServer();
    std::cout << "Juegos activos en el servidor:" << std::endl;
    for (const auto &juego : juegos) {
      std::cout << juego << std::endl;
    }
  } catch (const ProtocoloError &e) {
    std::cerr << "Error al recibir juegos activos: " << e.what() << std::endl;
  }

  // Verificando si hay un juego con el mismo nombre
  try {
    bool existeJuego = cliente.reciveMatchWithSameName();
    std::cout << "¿Existe juego con el mismo nombre? " << (existeJuego ? "Sí" : "No") << std::endl;
  } catch (const ProtocoloError &e) {
    std::cerr << "Error al verificar juego con el mismo nombre: " << e.what() << std::endl;
  }

  // Recibiendo presentación de color
  try {
    GameState estadoColor = cliente.reciveColorPresentationFromServer();
    std::cout << "Colores de jugadores recibidos:" << std::endl;
    for (const auto &playerColor : estadoColor.players_color) {
      std::cout << playerColor.first << " - " << playerColor.second << std::endl;
    }
  } catch (const ProtocoloError &e) {
    std::cerr << "Error al recibir presentación de color: " << e.what() << std::endl;
  }

  return 0;
}