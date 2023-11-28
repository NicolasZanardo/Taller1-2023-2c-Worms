#include "net_message_create_game.cpp"

NetMessageCreateGameResponse::NetMessageResponse(bool was_created)
    : NetMessage(NET_MESSAGE_TYPE_CREATE_GAME_RESPONSE)
    , was_created(was_created) {}

void NetMessageCreateGame::push_data_into(NetBuffer& container) {

}

void NetMessageCreateGame::pull_data_from(NetProtocolInterpreter& channel) {

}

void NetMessageCreateGame::execute(NetMessageBehaviour& interpreter) {

}
