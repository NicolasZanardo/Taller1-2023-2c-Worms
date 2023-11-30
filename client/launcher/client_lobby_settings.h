#ifndef __CLIENT_LOBBY_SETTINGS_H__
#define __CLIENT_LOBBY_SETTINGS_H__

#include <string>

#include "networking"

class ClientLobbySettings : public NetMessageBehaviour {
public:
    ClientLobbySettings()
    virtual ~ClientLobbySettings() = default;

    void run(NetMessageCreateGame* msg) override;
    void run(NetMessageJoinGame* msg) override;
    void run(NetMessageListGames* msg) override;

    inline bool isReadyToStart() const { this->ready_to_start; }

private:
    std::string game_room;
    std::string scenario;
    uint8_t joined_players;
    uint8_t total_players;

    bool ready_to_start;
};

#endif  // __CLIENT_LOBBY_SETTINGS_H__
