#include "games_manager.h"

#include <algorithm>
#include <iostream>
#include <utility>

#include "client.h"

bool GamesManager::createGame(const std::string& game_room, const std::string& scenario) {
    std::lock_guard<std::mutex> lck(this->mtx);

    if (this->rooms.find(game_room) == this->rooms.end()) {
        return false;
    }

    this->games.emplace_back(game_room, scenario);

    return true;
}

bool GamesManager::joinGame(const std::string& game_room, Client& client) {
    std::lock_guard<std::mutex> lck(this->mtx);

    auto iter = this->rooms.find(game_room);
    if (iter == this->rooms.end()) {
        return false;
    }

    this->rooms.join(Client& client);

    return true;
}
