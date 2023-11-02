#include "net_channel.h"
#include "net_buffer.h"
#include "net_protocol_interpreter.h"
#include "Messages/net_message_factory.h"

NetChannel::NetChannel(Socket skt) :
    socket(std::move(skt))
    {}

bool NetChannel::send_message(NetMessage& msg) {
    NetBuffer buffer;
    msg.push_data_into(buffer);

    return buffer.send_by(socket);
}

NetMessage* NetChannel::read_message() {
    return NetMessageFactory::recieve(socket);
}
