#include "GameActionCommand.h"
#include "Networking/Messages/net_message_game_action.h"

GameActionCommand::GameActionCommand(GameAction action): action(action) {}

std::shared_ptr<NetMessage> GameActionCommand::create_net_message(int client_id) const {
    return std::make_shared<NetMessageGameAction>(client_id, action);
}
