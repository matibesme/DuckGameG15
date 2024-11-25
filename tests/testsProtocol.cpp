#include "../src/client/protocolo_cliente.h" // Incluir la clase ProtocoloClient
#include "../src/server/protocolo_server.h"  // Incluir la clase ProtocoloServer
#include "socket.h"            // Incluir la clase Socket
#include <gtest/gtest.h>
#include <stdexcept> // Para lanzar excepciones

TEST(ProtocoloTest, CreateAndStartGame) {
  GameAccess game_access;
  game_access.action_type = CREATE_GAME;
  game_access.game_name = "game1";
  game_access.player1_name = "player1";
  game_access.player2_name = "player2";
  game_access.double_player = true;
  bool dead_connection = false;

  /// creo el hilo del cliente
  std::thread client([game_access, &dead_connection]() {
    ProtocoloCliente protocolo("localhost", "8080", dead_connection);
    protocolo.sendCreateJoinGameToServer(game_access);
    bool same_name = protocolo.reciveMatchWithSameName();
    ASSERT_EQ(same_name, false);

    GameAccess game_start;
    // Envio el mensaje de start game
    game_start.action_type = START_GAME;
    protocolo.sendRequestGameToServer(game_access);
  });

  // creo el socket aceptador
  Socket socket_aceptador("8080");
  Socket peer = socket_aceptador.accept();
  ProtocoloServer protocolo(std::move(peer), dead_connection, 1);
  GameAccess command = protocolo.receiveAccessFromClients();

  ASSERT_EQ(command.action_type, CREATE_GAME);
  ASSERT_EQ(command.game_name, "game1");
  ASSERT_EQ(command.player1_name, "player1");
  ASSERT_EQ(command.player2_name, "player2");
  ASSERT_EQ(command.double_player, true);

  protocolo.sendMatchWithSameName(false);

  command = protocolo.receiveAccessFromClients();
  ASSERT_EQ(command.action_type, CREATE_GAME);
  client.join();
}

// listar partidas y unirse a una partida
TEST(ProtocoloTest, ListAndJoinGame) {
  GameAccess game_access;
  game_access.action_type = LISTAR_PARTIDAS;
  bool dead_connection = false;

  // creo el hilo del cliente
  std::thread client([game_access, &dead_connection]() {
    ProtocoloCliente protocolo("localhost", "8080", dead_connection);
    protocolo.sendRequestGameToServer(game_access);
    std::list<std::string> list = protocolo.reciveActiveGamesFromServer();
    ASSERT_EQ(list.size(), 1);
    ASSERT_EQ(list.front(), "game1");

    GameAccess game_join;
    game_join.action_type = JOIN_GAME;
    game_join.game_name = "game1";
    game_join.player1_name = "player1";
    game_join.player2_name = "player2";
    game_join.double_player = true;
    protocolo.sendCreateJoinGameToServer(game_join);
  });

  // creo el socket aceptador
  Socket socket_aceptador("8080");
  Socket peer = socket_aceptador.accept();
  ProtocoloServer protocolo(std::move(peer), dead_connection, 1);
  GameAccess command = protocolo.receiveAccessFromClients();

  ASSERT_EQ(command.action_type, LISTAR_PARTIDAS);

  std::map<std::string, uint8_t> partidas;
  partidas.emplace("game1", 1);
  protocolo.sendActiveGames(partidas);

  command = protocolo.receiveAccessFromClients();
  ASSERT_EQ(command.action_type, JOIN_GAME);
  ASSERT_EQ(command.game_name, "game1");
  ASSERT_EQ(command.player1_name, "player1");
  ASSERT_EQ(command.player2_name, "player2");
  ASSERT_EQ(command.double_player, true);

  protocolo.sendMatchWithSameName(false);
  client.join();
}

// recibir al utilizar el handler
TEST(ProtocoloTest, proccesHandler) {
  bool dead_connection = false;

  std::thread client([&dead_connection]() {
    ProtocoloCliente protocolo("localhost", "8080", dead_connection);
    ClientAction command;
    command.type_of_movement = RIGHT;
    command.player = 1;
    protocolo.sendInGameToServer(command);
  });

  // creo el socket aceptador
  Socket socket_aceptador("8080");
  Socket peer = socket_aceptador.accept();
  ProtocoloServer protocolo(std::move(peer), dead_connection, 1);
  bool two_players = false;
  CommandClient command = protocolo.receiveCommandFromClients(two_players);
  ASSERT_EQ(command.type_of_movement, RIGHT);
  ASSERT_EQ(command.id, 1);
  client.join();
}

// recibir snapshot
TEST(ProtocoloTest, proccesSnapshot) {
  bool dead_connection = false;

  std::thread client([&dead_connection]() {
    ProtocoloCliente protocolo("localhost", "8080", dead_connection);

    // Recibo y verifico presentación de colores
    GameState command = protocolo.reciveFromServer();
    ASSERT_EQ(command.action, COLOR_PRESENTATION_BYTE);
    ASSERT_EQ(command.players_color.size(), 1);
    ASSERT_EQ(command.players_color["player1"], "color1");

    // Recibo y verifico estado completo del juego
    command = protocolo.reciveFromServer();
    ASSERT_EQ(command.action, FULL_GAME_BYTE);
    ASSERT_EQ(command.backGround_id, 1);

    // Verifico lista de plataformas
    ASSERT_EQ(command.lista_plataformas.size(), 1);
    auto platform =
        command.lista_plataformas.front(); // Acceso al primer elemento
    ASSERT_EQ(platform.type, TYPE_PLATFORM_DONUT);
    ASSERT_EQ(platform.x_pos, 1);
    ASSERT_EQ(platform.y_pos, 1);
    ASSERT_EQ(platform.width, 32);
    ASSERT_EQ(platform.height, 32);

    // Verifico lista de patos
    ASSERT_EQ(command.lista_patos.size(), 1);
    const auto &duck = command.lista_patos.front(); // Acceso al primer elemento
    ASSERT_EQ(duck.id, 1);
    ASSERT_EQ(duck.x_pos, 1);
    ASSERT_EQ(duck.y_pos, 1);
    ASSERT_EQ(duck.typeOfMove, 1);
    ASSERT_EQ(duck.typeOfGun, 1);
    ASSERT_EQ(duck.helmet, 1);
    ASSERT_EQ(duck.armor, 1);
    ASSERT_EQ(duck.is_aiming_up, true);
    ASSERT_EQ(duck.direction, RIGHT);

    // Verifico lista de balas
    ASSERT_EQ(command.lista_balas.size(), 1);
    const auto &bullet = command.lista_balas.front();
    ASSERT_EQ(bullet.id, 1);
    ASSERT_EQ(bullet.typeOfBullet, 1);
    ASSERT_EQ(bullet.x_pos, 1);
    ASSERT_EQ(bullet.y_pos, 1);
    ASSERT_EQ(bullet.orientation, RIGHT);

    // Verifico lista de armas
    ASSERT_EQ(command.lista_guns.size(), 1);
    const auto &gun = command.lista_guns.front();
    ASSERT_EQ(gun.typeOfGun, 1);
    ASSERT_EQ(gun.x_pos, 1);
    ASSERT_EQ(gun.y_pos, 1);

    // Verifico lista de cajas
    ASSERT_EQ(command.lista_boxes.size(), 1);
    const auto &box = command.lista_boxes.front();
    ASSERT_EQ(box.id, 1);
    ASSERT_EQ(box.x_pos, 1);
    ASSERT_EQ(box.y_pos, 1);

    // Verifico lista de cascos
    ASSERT_EQ(command.lista_helmets.size(), 1);
    const auto &helmet = command.lista_helmets.front();
    ASSERT_EQ(helmet.type, 1);
    ASSERT_EQ(helmet.x_pos, 1);
    ASSERT_EQ(helmet.y_pos, 1);

    // Verifico lista de armaduras
    ASSERT_EQ(command.lista_armors.size(), 1);
    const auto &armor = command.lista_armors.front();
    ASSERT_EQ(armor.type, 1);
    ASSERT_EQ(armor.x_pos, 1);
    ASSERT_EQ(armor.y_pos, 1);

    // Recibo y verifico fin de ronda
    command = protocolo.reciveFromServer();
    ASSERT_EQ(command.action, END_ROUND_BYTE);
    ASSERT_EQ(command.map_victorias.size(), 1);
    ASSERT_EQ(command.map_victorias["player1"], 1);

    // Recibo y verifico victoria
    command = protocolo.reciveFromServer();
    ASSERT_EQ(command.name_winner, "player1");
  });

  // Código de configuración del servidor (proporcionado en tu ejemplo)
  Socket socket_aceptador("8080");
  Socket peer = socket_aceptador.accept();
  ProtocoloServer protocolo(std::move(peer), dead_connection, 1);

  GameState gameState;

  // Envío de datos al cliente (como en tu código)
  gameState.action = COLOR_PRESENTATION_BYTE;
  std::map<std::string, std::string> players_color;
  players_color.emplace("player1", "color1");
  gameState.players_color = players_color;
  protocolo.sendPlayersColor(players_color);

  gameState.action = FULL_GAME_BYTE;
  gameState.backGround_id = 1;
  DTOPlatform platform = {TYPE_PLATFORM_DONUT, 1, 1, 32, 32};
  gameState.lista_plataformas.push_back(platform);

  DTODuck duck = {1, "color1", 1, 1, 1, 1, 1, 1, true, RIGHT};
  gameState.lista_patos.push_back(duck);

  DTOBullet bullet = {1, 1, 1, 1, RIGHT};
  gameState.lista_balas.push_back(bullet);

  DTOGuns gun = {1, 1, 1};
  gameState.lista_guns.push_back(gun);

  DTOBoxes box = {1, 1, 1};
  gameState.lista_boxes.push_back(box);

  Protection helmet = {1, 1, 1};
  gameState.lista_helmets.push_back(helmet);

  Protection armor = {1, 1, 1};
  gameState.lista_armors.push_back(armor);

  protocolo.sendFullGame(gameState);

  gameState.action = END_ROUND_BYTE;
  std::map<std::string, uint8_t> roundsWin;
  roundsWin.emplace("player1", 1);
  gameState.map_victorias = roundsWin;
  protocolo.sendEndRound(gameState);

  gameState.name_winner = "player1";
  protocolo.sendVictory(gameState);

  client.join();
}
