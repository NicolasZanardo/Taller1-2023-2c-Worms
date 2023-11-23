#include "net_message_game_action.h"

NetMessageGameAction::NetMessageGameAction()
        : NetMessage(NET_MESSAGE_TYPE_GAME_ACTION)
{}

NetMessageGameAction::NetMessageGameAction(size_t client_id, GameAction action)
        : NetMessage(NET_MESSAGE_TYPE_GAME_ACTION),
          client_id(client_id), action(action)
{}

void NetMessageGameAction::push_data_into(NetBuffer& container) {
    NetMessage::push_data_into(container);
    container.push_uint(client_id);
    container.push_byte(static_cast<uint8_t>(action));
}

void NetMessageGameAction::pull_data_from(NetProtocolInterpreter& channel) {
    client_id = channel.read_uint();
    action = static_cast<GameAction>(channel.read_byte());
}

void NetMessageGameAction::execute(NetMessageBehaviour& interpreter) {
    interpreter.run(this);
}