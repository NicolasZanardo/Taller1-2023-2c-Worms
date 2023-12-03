#ifndef __SERVER_GAMES_MANAGER_H__
#define __SERVER_GAMES_MANAGER_H__

#include <cstdint>

#include <list>
#include <map>
#include <mutex>
#include <stdexcept>
#include <string>

#include "game_room.h"

#include "../../../common_base/Game/game_info_dto.h"

class Client;


class GamesManager {
public:
    GamesManager() = default;
    ~GamesManager() = default;

    GamesManager(const GamesManager& other) = delete;
    GamesManager& operator=(const GamesManager& other) = delete;

    GamesManager(GamesManager& other) = delete;
    GamesManager& operator=(GamesManager&& other) = delete;

    bool createGame(const std::string& game_room, const std::string& scenario, uint8_t total_players);
    bool joinGame(const std::string& game_room, Client& client);
    std::list<GameInfoDTO> listGames();

    void cleanEndedGames();

private:
    std::map<std::string, GameRoom> rooms;

    std::mutex mtx;
};

#endif  // __SERVER_GAMES_MANAGER_H__