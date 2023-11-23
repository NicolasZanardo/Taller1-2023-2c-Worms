
#ifndef TP_WORMS_GAMEACTIONCOMMAND_H
#define TP_WORMS_GAMEACTIONCOMMAND_H

#include "Command.h"
#include "Game/GameAction.h"

class GameActionCommand : public Command {
    GameAction action;
public:
    explicit GameActionCommand(GameAction action);
    std::shared_ptr<NetMessage> create_net_message(int client_id) const override;
};


#endif //TP_WORMS_GAMEACTIONCOMMAND_H
