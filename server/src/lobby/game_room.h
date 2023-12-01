#ifndef __SERVER_GAME_ROOM_H__
#define __SERVER_GAME_ROOM_H__

#include <list>
#include <string>

class Client;

class GameRoom {
public:
    GameRoom() = default;
    explicit GameRoom(const std::string& game_room, const std::string& scenario);
    ~GameRoom() = default;

    void join(Client& client);

    const std::string& getName() const { return this->game_room; }
    const std::string& getScenario() const { return this->scenario; }

private:
    std::string game_room;
    std::string scenario_name;
    std::list<Client&> players;
};

#endif  // __SERVER_GAME_ROOM_H__
