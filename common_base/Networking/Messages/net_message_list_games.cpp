#include "net_message_list_games.h"

NetMessageListGames::NetMessageListGames()
    : NetMessage(NET_MESSAGE_TYPE_LIST_GAMES) {}

void NetMessageListGames::push_data_into(NetBuffer& container) {
    NetMessage::push_data_into(container);
}

void NetMessageListGames::pull_data_from(NetProtocolInterpreter& channel) { }

void NetMessageListGames::execute(NetMessageBehaviour& interpreter) {
    interpreter.run(this);
}
