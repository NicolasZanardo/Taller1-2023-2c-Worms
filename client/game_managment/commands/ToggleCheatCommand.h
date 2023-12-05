#ifndef TP_WORMS_TOGGLECHEATCOMMAND_H
#define TP_WORMS_TOGGLECHEATCOMMAND_H

#include "Command.h"
#include "Game/CheatType.h"

class ToggleCheatCommand : public Command {
    CheatType cheat;
public:
    explicit ToggleCheatCommand(CheatType cheat);
    std::shared_ptr<NetMessage> create_net_message(int client_id) const override;
};



#endif //TP_WORMS_TOGGLECHEATCOMMAND_H
