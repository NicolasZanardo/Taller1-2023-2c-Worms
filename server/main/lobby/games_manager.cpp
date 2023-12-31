#include "games_manager.h"

#include <iostream>
#include <utility>

#include "client/server_client.h"

GamesManager::GamesManager()
    : rooms() {}

bool GamesManager::createGame(const std::string& game_room, const std::string& scenario, uint16_t total_players) {
    std::lock_guard<std::mutex> lck(this->mtx);
    if ((this->rooms.find(game_room) != this->rooms.end())) {
        return false;
    }

    this->rooms.emplace(std::make_pair(game_room, GameRoom(game_room, scenario, total_players)));
    return true;
}

bool GamesManager::joinGame(const std::string& game_room, Client& client) {
    std::lock_guard<std::mutex> lck(this->mtx);

    auto iter = this->rooms.find(game_room);
    if (iter == this->rooms.end()) {
        return false;
    }

    iter->second.join(client);

    return true;
}

std::list<GameInfoDTO> GamesManager::listGames() {
    std::list<GameInfoDTO> info_list;
    
    for (auto& game : this->rooms) {
        info_list.push_back(std::move(game.second.getInfo()));
    }

    return info_list;
}

bool GamesManager::startGame(const std::string& game_room) {
    std::lock_guard<std::mutex> lck(this->mtx);

    auto iter = this->rooms.find(game_room);
    if (iter == this->rooms.end()) {
        return false;
    }

    iter->second.start();
    return true;
}

void GamesManager::cleanEndedGames() {
    std::lock_guard<std::mutex> lck(this->mtx);

    for (auto it = this->rooms.begin(); it != this->rooms.end();)
    {
        if (it->second.wasEnded()) {
            it = this->rooms.erase(it);
        } else {
            ++it;
        }
    }
}
