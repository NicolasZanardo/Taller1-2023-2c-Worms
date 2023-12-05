#include "ToggleCheatCommand.h"
#include "Networking/Messages/net_message_player_toggle_cheat.h"

ToggleCheatCommand::ToggleCheatCommand(CheatType cheat): cheat(cheat) {}

std::shared_ptr<NetMessage> ToggleCheatCommand::create_net_message(int client_id) const {
    return std::make_shared<NetMessagePlayerToggleCheat>(client_id, cheat);
}