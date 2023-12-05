#ifndef __CLIENT_LOBBY_SETTINGS_H__
#define __CLIENT_LOBBY_SETTINGS_H__

#include <string>

#include "networking.h"

#include "../../common_base/Game/game_info_dto.h"
#include "../game/client_game_state_dto.h"

class ClientLobbySettings : public NetMessageBehaviour {
public:
    ClientLobbySettings();
    virtual ~ClientLobbySettings() = default;

    void run(NetMessageChat* msg) override { }
    void run(NetMessageLeave* msg) override { }
    void run(NetMessage_test* msg) override { }
    void run(NetMessageInformID* msg) override;
    void run(NetMessageInitialGameState* msg) override;
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

    void run(NetMessageGameEnded* msg) override { }
    
    int id;
    std::shared_ptr<ClientGameStateDTO> game_state_dto;
    std::list<GameInfoDTO> games_info;

private:
    std::string game_room;
    std::string scenario;
    uint8_t joined_players;
    uint8_t total_players;
    bool ready_to_start;
};

#endif  // __CLIENT_LOBBY_SETTINGS_H__
