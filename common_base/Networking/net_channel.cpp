#include "net_channel.h"
#include "net_buffer.h"
#include "net_protocol_interpreter.h"
#include "Messages/net_message_factory.h"

NetChannel::NetChannel(Socket skt) :
    socket(std::move(skt)),
    socket_open(true)
    {}

bool NetChannel::send_message(NetMessage& msg) {
    NetBuffer buffer;
    msg.push_data_into(buffer);

    try {
        socket_open = buffer.send_by(socket);
        return socket_open;
    } catch (...) {
        socket_open = false;
        throw;
    }
}

NetMessage* NetChannel::read_message() {
    try {
        return NetMessageFactory::recieve(socket);
    } catch (...) {
        socket_open = false;
        throw;
    }
}

const bool NetChannel::is_open() const {
    return socket_open;
}