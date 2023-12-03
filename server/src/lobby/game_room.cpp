#include "game_room.h"

#include <stdexcept>

#include "../client/client.h"  // Del server.

GameRoom::GameRoom()
    : was_ended(false) {}

GameRoom::GameRoom(const std::string& game_room, const std::string& scenario)
    : game_room(game_room)
    , scenario(scenario) {}

void GameRoom::join(Client& client) {
    if (this->players.find(client.getID()) != this->players.end()) {
        throw std::runtime_error("This id was alredy joined.\n");
    }

    this->players.emplace(client.getID(), client);
}

void GameRoom::leave(Client& client) {
    if (this->players.find(client.getID()) == this->players.end()) {
        throw std::runtime_error("This id was not joined.\n");
    }

    this->players.erase(client.getID());
}

void GameRoom::start() {
    std::cout << "Starting game ...\n";
}
