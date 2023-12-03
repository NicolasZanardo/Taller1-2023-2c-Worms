#include "net_message_list_games_response.h"

NetMessageListGamesResponse::NetMessageListGamesResponse()
    : NetMessage(NET_MESSAGE_TYPE_LIST_GAMES_RESPONSE) {}

void NetMessageListGamesResponse::push_data_into(NetBuffer& container) {
    NetMessage::push_data_into(container);
}

void NetMessageListGamesResponse::pull_data_from(NetProtocolInterpreter& channel) { }

void NetMessageListGamesResponse::execute(NetMessageBehaviour& interpreter) {
    interpreter.run(this);
}
