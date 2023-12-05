#include "net_channel.h"
#include "net_buffer.h"
#include "net_protocol_interpreter.h"
#include "Messages/net_message_factory.h"
#include "socket_connection_lost_error.h"

NetChannel::NetChannel(Socket skt) :
    socket(std::move(skt)),
    socket_open(true)
    {}

NetChannel::NetChannel(const char *host, const char* service)
    : socket(host, service)
    , socket_open(true) {}

bool NetChannel::send_message(NetMessage& msg) {
    NetBuffer buffer;
    msg.push_data_into(buffer);

    try {
        socket_open = buffer.send_by(socket);
    } catch (...) {
        socket_open = false;
    }
    return socket_open;
}

NetMessage* NetChannel::read_message() {
    try {
        return NetMessageFactory::recieve(socket);
    } catch (...) {
        socket_open = false;
        throw SocketConnectionLost(&socket);
    }
}

const bool NetChannel::is_open() const {
    return socket_open;
}

void NetChannel::dissconect() {
    socket.shutdown(2);
    socket.close();
    socket_open = false;
}
