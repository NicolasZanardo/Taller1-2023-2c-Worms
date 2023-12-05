#ifndef __SERVER_GAME_ROOM_H__
#define __SERVER_GAME_ROOM_H__

#include <cstdint>
#include <string>
#include <list>
#include <unordered_map>
#include "game_info_dto.h"

class GameEngineInstance;

class Client;

class GameRoom {
public:
    GameRoom();
    explicit GameRoom(const std::string& name, const std::string& scenario, uint8_t total_players);
    ~GameRoom() = default;

    void join(Client& client);
    void leave(Client& client);
    void start();

    
    const std::string& getName() const { return this->name; }
    const std::string& getScenario() const { return this->scenario; }
    bool wasEnded() const { return this->was_ended; }
    
    GameInfoDTO getInfo() const;

    void setEnd() { this->was_ended = true; }

private:
    std::string name;
    std::string scenario;
    uint8_t total_players;

    std::unordered_map<uint32_t, Client&> players;
    std::list<Client*> list_clients;

    GameEngineInstance* game_instance;

    bool was_ended;
};

#endif  // __SERVER_GAME_ROOM_H__
