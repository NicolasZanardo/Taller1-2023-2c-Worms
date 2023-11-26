#include "net_message_inform_id.h"

NetMessageInformID::NetMessageInformID()
    : NetMessage(NET_MESSAGE_TYPE_INFORM_ID)
    {}


NetMessageInformID::NetMessageInformID(int client_id)
    : NetMessage(NET_MESSAGE_TYPE_INFORM_ID),
    client_id(client_id)
    {}

void NetMessageInformID::push_data_into(NetBuffer& container) {
    NetMessage::push_data_into(container);
    container.push_int(client_id);
}

void NetMessageInformID::pull_data_from(NetProtocolInterpreter& channel) {
    client_id = channel.read_int();
}

void NetMessageInformID::execute(NetMessageBehaviour& interpreter) {
    interpreter.run(this);
}
