#include "gtest/gtest.h"
#include "protocolo_server.h"
#include "game_exception.h"
#include "../common/socket.h"
#include <iostream>
#include <string>

int main() {
  // Simulando una conexión
  bool dead_connection = false;
  Socket socket("localhost", "8080");
  ProtocoloServer servidor(std::move(socket), dead_connection, 1);

  // Creando un estado de juego
  GameState estado;
  estado.action = FULL_GAME_BYTE;
  estado.backGround_id = 1;

  // Añadiendo plataformas al estado del juego
  estado.lista_plataformas.push_back({1, 0.0f, 0.0f, 100.0f, 50.0f});
  estado.lista_plataformas.push_back({2, 200.0f, 150.0f, 150.0f, 60.0f});

  // Añadiendo patos
  estado.lista_patos.push_back({1, "Duck1", 50.0f, 100.0f, 0, 1, 0, 0, false, 1});
  estado.lista_patos.push_back({2, "Duck2", 150.0f, 200.0f, 1, 0, 1, 1, true, 2});

  // Enviando estado de juego al cliente
  std::cout << "Enviando estado completo de juego al cliente..." << std::endl;
  servidor.sendToClient(estado);

  // Enviando fin de ronda
  GameState finDeRonda;
  finDeRonda.action = END_ROUND_BYTE;
  finDeRonda.map_victorias = {{"Jugador1", 5}, {"Jugador2", 3}};
  std::cout << "Enviando fin de ronda al cliente..." << std::endl;
  servidor.sendToClient(finDeRonda);

  // Enviando victoria
  GameState victoria;
  victoria.action = VICTORY_BYTE;
  victoria.name_winner = "Jugador1";
  std::cout << "Enviando victoria al cliente..." << std::endl;
  servidor.sendToClient(victoria);

  // Enviando presentación de color
  GameState colorPresentacion;
  colorPresentacion.action = COLOR_PRESENTATION_BYTE;
  colorPresentacion.players_color = {{"Jugador1", "Rojo"}, {"Jugador2", "Azul"}};
  std::cout << "Enviando presentación de color al cliente..." << std::endl;
  servidor.sendToClient(colorPresentacion);

  return 0;
}
