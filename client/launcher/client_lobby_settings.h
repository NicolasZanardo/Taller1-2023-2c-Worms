#ifndef __CLIENT_LOBBY_SETTINGS_H__
#define __CLIENT_LOBBY_SETTINGS_H__

#include <string>

#include "networking.h"

class ClientLobbySettings : public NetMessageBehaviour {
public:
    ClientLobbySettings();
    virtual ~ClientLobbySettings() = default;

    void run(NetMessageChat* msg) override { }
    void run(NetMessageLeave* msg) override { }
    void run(NetMessage_test* msg) override { }
    void run(NetMessageInformID* msg) override;
    void run(NetMessageInitialGameState* msg) override { }
    void run(NetMessageGameStateUpdate* msg) override { }
    void run(NetMessageGameAction* msg) override { }
    void run(NetMessagePlayerChangedWeapon* msg) override { }
    void run(NetMessagePlayerChangedProjectileCountdown* msg) override { }

    void run(NetMessageCreateGame* msg) override { }
    void run(NetMessageListGames* msg) override { }
    void run(NetMessageJoinGame* msg) override { }

    void run(NetMessageCreateGameResponse* msg) override;
    void run(NetMessageJoinGameResponse* msg) override;
    void run(NetMessageListGamesResponse* msg) override;

    void run(NetMessageStartGame* msg) override;

    bool isReadyToStart() const { return this->ready_to_start; }
    
    int id;

private:
    std::string game_room;
    std::string scenario;
    uint8_t joined_players;
    uint8_t total_players;
    bool ready_to_start;
};

#endif  // __CLIENT_LOBBY_SETTINGS_H__
