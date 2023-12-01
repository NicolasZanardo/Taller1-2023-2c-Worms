#include "server_game_room.h"

#include "client.h"  // Del server.

Game::Game(const std::string& game_room, const std::string& scenario)
    : game_room(game_room)
    , scenario_name(scenario_name) {}

void Game::join(Client& client) {
    this->players.push_back(client);
}
