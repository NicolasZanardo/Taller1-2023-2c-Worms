#include "net_message_create_game_response.cpp"

NetMessageCreateGameResponse::NetMessageResponse()
    : NetMessage(NET_MESSAGE_TYPE_CREATE_GAME_RESPONSE) {}

NetMessageCreateGameResponse::NetMessageResponse(bool was_created)
    : NetMessage(NET_MESSAGE_TYPE_CREATE_GAME_RESPONSE)
    , was_created(was_created) {}

void NetMessageCreateGame::push_data_into(NetBuffer& container) {
    NetMessage::push_data_into(container);
    container.push_bool(this->was_created);
}

void NetMessageCreateGame::pull_data_from(NetProtocolInterpreter& channel) {
    this->was_created = channel.read_bool();
}

void NetMessageCreateGame::execute(NetMessageBehaviour& interpreter) {
    interpreter.run(this);
}
