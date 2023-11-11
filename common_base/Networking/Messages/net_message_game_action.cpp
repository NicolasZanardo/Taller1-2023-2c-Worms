#include "net_message_game_action.h"

NetMessageGameAction::NetMessageGameAction()
        : NetMessage(NET_MESSAGE_TYPE_GAME_ACTION)
{}

NetMessageGameAction::NetMessageGameAction(size_t client_id, ActionTypeDto action)
        : NetMessage(NET_MESSAGE_TYPE_GAME_ACTION),
          client_id(client_id), action(action)
{}

void NetMessageGameAction::push_data_into(NetBuffer& container) {
    NetMessage::push_data_into(container);
    container.push_uint(client_id);
}

void NetMessageGameAction::pull_data_from(NetProtocolInterpreter& channel) {
    client_id = channel.read_uint();
}

void NetMessageGameAction::execute(NetMessageBehaviour& interpreter) {
    interpreter.run(this);
}