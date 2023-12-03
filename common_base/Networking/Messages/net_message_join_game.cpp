#include "net_message_join_game.cpp"

NetMessageJoinGame::NetMessageJoinGame()
    : NetMessage(NET_MESSAGE_TYPE_JOIN_GAME) {}

NetMessageJoinGame::NetMessageJoinGame(const std::string& game_room)
    : NetMessage(NET_MESSAGE_TYPE_JOIN_GAME)
    , game_room(game_room) {}

void NetMessageJoinGame::push_data_into(NetBuffer& container) {
    NetMessage::push_data_into(container);
    container.push_string(this->game_room);
}

void NetMessageJoinGame::pull_data_from(NetProtocolInterpreter& channel) {
    this->game_room = channel.read_string();
}

void NetMessageJoinGame::execute(NetMessageBehaviour& interpreter) {
    interpreter.run(this);
}
