#ifndef SERVER_GAMENETMESSAGEBEHAVIOUR_H
#define SERVER_GAMENETMESSAGEBEHAVIOUR_H

#include "../../../common_base/networking.h"
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
    void run(NetMessagePlayerShot* msg) override;

public:
    GameNetMessageBehaviour(InGameClients& gameClients, GameInstance& game);

};


#endif