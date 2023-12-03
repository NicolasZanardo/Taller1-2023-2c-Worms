#ifndef __SERVER_GAMES_MANAGER_H__
#define __SERVER_GAMES_MANAGER_H__

#include <cstdint>

#include <map>
#include <mutex>
#include <stdexcept>
#include <string>

#include "game_room.h"

class Client;

// class GameAlredyExists : public std::runtime_error {
// public:
//     GameAlredyExists() : std::runtime_error("Game Alredy Exists.") {}
// };


// class GameNotExists : public std::runtime_error {
// public:
//     GameNotExists() : std::runtime_error("Game Not Exists.") {}
// };

class GamesManager {
public:
    GamesManager() = default;
    ~GamesManager() = default;

    GamesManager(const GamesManager& other) = delete;
    GamesManager& operator=(const GamesManager& other) = delete;

    GamesManager(GamesManager& other) = delete;
    GamesManager& operator=(GamesManager&& other) = delete;

    bool createGame(const std::string& game_room, const std::string& scenario);
    bool joinGame(const std::string& game_room, Client& client);
    void cleanEndedGames();

private:
    std::map<std::string, GameRoom> rooms;

    std::mutex mtx;
};

#endif  // __SERVER_GAMES_MANAGER_H__