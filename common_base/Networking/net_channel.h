#ifndef COMMON_NET_CHANNEL_H_
#define COMMON_NET_CHANNEL_H_

#include "../socket.h"
#include "Messages/net_message.h"

class NetChannel {
    Socket socket;
    public:
    explicit NetChannel(Socket skt);

    bool send_message(NetMessage& msg);
    NetMessage* read_message();
};
#endif
