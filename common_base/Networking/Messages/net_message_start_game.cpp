#include "net_message_start_game.h"

NetMessageStartGame::NetMessageStartGame()
    : NetMessage(NET_MESSAGE_TYPE_START_GAME) {}

void NetMessageStartGame::push_data_into(NetBuffer& container) {
    NetMessage::push_data_into(container);
}

void NetMessageStartGame::pull_data_from(NetProtocolInterpreter& channel) { }

void NetMessageStartGame::execute(NetMessageBehaviour& interpreter) {
    interpreter.run(this);
}
