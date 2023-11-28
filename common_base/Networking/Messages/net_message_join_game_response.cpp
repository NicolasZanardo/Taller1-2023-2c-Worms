#include "net_message_join_game.cpp"

NetMessageJoinGame::NetMessageJoinGame(bool was_joined)
    : NetMessage(NET_MESSAGE_TYPE_JOIN_GAME_RESPONSE)
    , was_joined(was_joined) {}

void NetMessageJoinGame::push_data_into(NetBuffer& container) {

}

void NetMessageJoinGame::pull_data_from(NetProtocolInterpreter& channel) {

}

void NetMessageJoinGame::execute(NetMessageBehaviour& interpreter) {

}
