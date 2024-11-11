#include "lobby_partidas.h"

LobbyPartidas::LobbyPartidas(): id_partida(0),partidas(), protected_queues_sender(), queues_sender(),
    queues_game_loop(), id_hoster_partida(), end_game(),
    map_id_clientes(), partidas_sin_arrancar(), m()
{
}

std::shared_ptr<BlockingQueue<CommandClient>> LobbyPartidas::addPartida(uint8_t id_client)
{

    std::lock_guard<std::mutex> lock(m);
    end_game[id_partida] = false;

    queues_game_loop.emplace(id_partida, std::make_shared<BlockingQueue<CommandClient>>(50));
    protected_queues_sender.emplace(id_partida, std::make_unique<ProtectedQueuesMap>());
    partidas.emplace(id_partida, std::make_unique<GameLoop>(queues_game_loop[id_partida], end_game[id_partida], protected_queues_sender[id_partida], map_id_clientes[id_partida]));
    id_hoster_partida[id_client] = id_partida;
    protected_queues_sender[id_partida]->addClient(id_client, *queues_sender[id_client]);
    map_id_clientes[id_partida].push_back(id_client);
    partidas_sin_arrancar.emplace(id_partida++, id_client);
    return queues_game_loop[id_partida-1];
}

std::shared_ptr<BlockingQueue<CommandClient>> LobbyPartidas::joinGame(uint8_t id_partida, uint8_t id_cliente)
{
    std::lock_guard<std::mutex> lock(m);
    if (partidas_sin_arrancar.find(id_partida) == partidas_sin_arrancar.end())
    {
      return nullptr;
    }

    protected_queues_sender[id_partida]->addClient(id_cliente, *queues_sender[id_cliente]);
    map_id_clientes[id_partida].push_back(id_cliente);
    return queues_game_loop[id_partida];
}




bool LobbyPartidas::isHoster(uint8_t id_cliente)
{
    return id_hoster_partida.find(id_cliente) != id_hoster_partida.end();
}

void LobbyPartidas::startGame(uint8_t id_client)
{
    std::lock_guard<std::mutex> lock(m);
    partidas[id_hoster_partida[id_client]]->start();
    partidas_sin_arrancar.erase(id_hoster_partida[id_client]);
}


void LobbyPartidas::addQueueSender(uint8_t id_player, std::shared_ptr<BlockingQueue<GameState>> queue)
{
    std::lock_guard<std::mutex> lock(m);
    queues_sender.emplace(id_player, queue);
}

void LobbyPartidas::removeQueue(uint8_t id)
{
    std::lock_guard<std::mutex> lock(m);
    protected_queues_sender[id]->removeQueue(id);
}

void LobbyPartidas::removeGame(uint8_t id)
{
    std::lock_guard<std::mutex> lock(m);
    end_game[id] = true;
    queues_game_loop[id]->close();
    queues_game_loop.erase(id);
    partidas[id]->join();
    partidas.erase(id);
}

std::map<uint8_t, uint8_t>& LobbyPartidas::getIdPartidas()
{
    std::lock_guard<std::mutex> lock(m);
    return partidas_sin_arrancar;

}


LobbyPartidas::~LobbyPartidas()
{
    for (auto& it: partidas)
    {
        end_game[it.first] = true;
        queues_game_loop[it.first]->close();
        queues_game_loop.erase(it.first);
        partidas[it.first]->join();
        partidas.erase(it.first);
    }

}