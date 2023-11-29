#include "net_message_game_ended.h"

NetMessageGameEnded::NetMessageGameEnded()
    : NetMessage(NET_MESSAGE_TYPE_GAME_ENDED)
{}

NetMessageGameEnded::NetMessageGameEnded(int winner_client_id)
    : NetMessage(NET_MESSAGE_TYPE_GAME_ENDED),
      winner_client_id(winner_client_id)
{}

void NetMessageGameEnded::push_data_into(NetBuffer& container) {
    NetMessage::push_data_into(container);
    container.push_int(winner_client_id);
}

void NetMessageGameEnded::pull_data_from(NetProtocolInterpreter& channel) {
    winner_client_id = channel.read_int();
}

void NetMessageGameEnded::execute(NetMessageBehaviour& interpreter) {
    interpreter.run(this);
}