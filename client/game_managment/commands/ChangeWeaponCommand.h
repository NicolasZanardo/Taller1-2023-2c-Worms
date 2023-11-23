#ifndef TP_WORMS_CHANGEWEAPONCOMMAND_H
#define TP_WORMS_CHANGEWEAPONCOMMAND_H

#include "Command.h"
#include "Game/WeaponTypeDto.h"

class ChangeWeaponCommand : public Command {
    WeaponTypeDto weapon;
public:
    explicit ChangeWeaponCommand(WeaponTypeDto weapon);
    std::shared_ptr<NetMessage> create_net_message(int client_id) const override;
};

#endif
