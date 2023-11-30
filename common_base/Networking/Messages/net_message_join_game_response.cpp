#include "net_message_join_game_response.cpp"

NetMessageJoinGameResponse::NetMessageJoinGameResponse()
    : was_joined(was_joined) {}

NetMessageJoinGameResponse::NetMessageJoinGameResponse(bool was_joined)
    : NetMessage(NET_MESSAGE_TYPE_JOIN_GAME_RESPONSE)
    , was_joined(was_joined) {}

void NetMessageJoinGameResponse::push_data_into(NetBuffer& container) {
    NetMessage::push_data_into(container);
    container.push_bool(this->was_created);
}

void NetMessageJoinGameResponse::pull_data_from(NetProtocolInterpreter& channel) {
    this->was_created = channel.read_bool();
}

void NetMessageJoinGameResponse::execute(NetMessageBehaviour& interpreter) {
    interpreter.run(this);
}
