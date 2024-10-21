#include "lobby_partidas.h"


LobbyPartidas::LobbyPartidas(): partidas(), queues_comandos(), maps_queues_sender(),cantidad_partidas(0) {}

LobbyPartidas::addGame(uint8_t client_id) {
    uint16_t id += cantidad_partidas;
    maps_queues_sender[id] = new ProtectedQueuesMap();
    maps_queues_sender[id].addClient(client_id, queue_sender);
    queues_comandos[id] = new BlockingQueue<CommandGame>();

    partidas[id] = new GameLoop(queues_comandos[id], maps_queues_sender[id]);
  
    return queues_comandos[id];
}


LobbyPartidas::joinGame(uint16_t id,client_id) {
    if (partidas.find(id) == partidas.end()) {
        throw GameException("Partida no encontrada");
    }
    maps_queues_sender[id].addClient(client_id, queue_sender);
    return queues_comandos[id];
}