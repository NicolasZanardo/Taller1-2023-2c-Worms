#ifndef TP_WORMS_CHANGEPROJECTILECOUNTDOWNCOMMAND_H
#define TP_WORMS_CHANGEPROJECTILECOUNTDOWNCOMMAND_H

#include "Command.h"
#include "Game/ProjectileCountDown.h"

class ChangeProjectileCountDownCommand : public Command {
    ProjectileCountDown countdown;
public:
    explicit ChangeProjectileCountDownCommand(ProjectileCountDown countdown);

    std::shared_ptr <NetMessage> create_net_message(int client_id) const override;
};


#endif //TP_WORMS_CHANGEPROJECTILECOUNTDOWNCOMMAND_H
