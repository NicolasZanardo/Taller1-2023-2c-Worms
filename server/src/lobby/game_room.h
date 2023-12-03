#ifndef __SERVER_GAME_ROOM_H__
#define __SERVER_GAME_ROOM_H__

#include <cstdint>
#include <string>
#include <unordered_map>

class Client;

class GameRoom {
public:
    GameRoom();
    explicit GameRoom(const std::string& game_room, const std::string& scenario);
    ~GameRoom() = default;

    void join(Client& client);
    void leave(Client& client);
    void start();

    const std::string& getName() const { return this->game_room; }
    const std::string& getScenario() const { return this->scenario; }
    bool wasEnded() const { return this->was_ended; }

    void setEnd() { this->was_ended = true; }

private:
    std::string game_room;
    std::string scenario;
    std::unordered_map<uint32_t, Client&> players;

    bool was_ended;
};

#endif  // __SERVER_GAME_ROOM_H__
