#include "net_message_join_game.cpp"

NetMessageJoinGame::NetMessageJoinGame(const std::string& game_room, uint8_t num_players)
    : NetMessage(NET_MESSAGE_TYPE_JOIN_GAME)
    , game_room(game_room) {}

void NetMessageJoinGame::push_data_into(NetBuffer& container) {

}

void NetMessageJoinGame::pull_data_from(NetProtocolInterpreter& channel) {

}

void NetMessageJoinGame::execute(NetMessageBehaviour& interpreter) {

}
