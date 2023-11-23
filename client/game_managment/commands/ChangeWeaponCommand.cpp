#include "ChangeWeaponCommand.h"
#include "Networking/Messages/net_message_player_changed_weapon.h"

ChangeWeaponCommand::ChangeWeaponCommand(WeaponTypeDto weapon) : weapon(weapon) {}

std::shared_ptr<NetMessage> ChangeWeaponCommand::create_net_message(int client_id) const {
    return std::make_shared<NetMessagePlayerChangedWeapon>(client_id, weapon);
}
