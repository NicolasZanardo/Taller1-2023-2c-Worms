#ifndef SERVER_GAMENETMESSAGEBEHAVIOUR_H
#define SERVER_GAMENETMESSAGEBEHAVIOUR_H

#include "../../../../common_base/networking.h"
#include "InGameClients.h"
#include "GameInstance.h"

class GameNetMessageBehaviour: public NetMessageBehaviour{

    InGameClients& gameClients;
    GameInstance& game;

    void run(NetMessageChat* msg) override;
    void run(NetMessageLeave* msg) override;
    void run(NetMessage_test* msg) override;
    void run(NetMessageInformID* msg) override;
    void run(NetMessageInitialGameState* msg) override;
    void run(NetMessageGameStateUpdate* msg) override;
    void run(NetMessageGameAction* msg) override;
    void run(NetMessagePlayerChangedWeapon* msg) override;
    void run(NetMessagePlayerChangedProjectileCountdown* msg) override;

    void run(NetMessageCreateGame* msg) override { }
    void run(NetMessageListGames* msg) override { }
    void run(NetMessageJoinGame* msg) override { }

    void run(NetMessageCreateGameResponse* msg) override { }
    void run(NetMessageJoinGameResponse* msg) override { }
    void run(NetMessageListGamesResponse* msg) override { }

    void run(NetMessageStartGame* msg) override { }

public:
    GameNetMessageBehaviour(InGameClients& gameClients, GameInstance& game);

};


#endif
