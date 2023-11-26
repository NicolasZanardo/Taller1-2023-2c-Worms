#include "net_message_leave.h"

NetMessageLeave::NetMessageLeave()
    : NetMessage(NET_MESSAGE_TYPE_LEAVE)
    {}


NetMessageLeave::NetMessageLeave(int client_id)
    : NetMessage(NET_MESSAGE_TYPE_LEAVE),
    client_id(client_id)
    {}

void NetMessageLeave::push_data_into(NetBuffer& container) {
    NetMessage::push_data_into(container);
    container.push_int(client_id);
}

void NetMessageLeave::pull_data_from(NetProtocolInterpreter& channel) {
    client_id = channel.read_int();
}

void NetMessageLeave::execute(NetMessageBehaviour& interpreter) {
    interpreter.run(this);
}
