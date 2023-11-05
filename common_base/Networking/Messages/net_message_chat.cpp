#include "net_message_chat.h"

NetMessageChat::NetMessageChat()
    : NetMessage(NET_MESSAGE_TYPE_CHAT)
    {}


NetMessageChat::NetMessageChat(const int client_id, const std::string chat)
    : NetMessage(NET_MESSAGE_TYPE_CHAT),
    client_id(client_id),
    chat(chat)
    {}

void NetMessageChat::push_data_into(NetBuffer& container) {
    NetMessage::push_data_into(container);
    container.push_uint(client_id);
    container.push_string(chat);
}

void NetMessageChat::pull_data_from(NetProtocolInterpreter& channel) {
    client_id = channel.read_uint();
    chat = channel.read_string();
}
