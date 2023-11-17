#ifndef COMMON_NET_CHANNEL_H_
#define COMMON_NET_CHANNEL_H_

#include "../socket.h"
#include "Messages/net_message.h"

class NetChannel {
    Socket socket;
    bool socket_open;

    public:
    explicit NetChannel(Socket skt);
    explicit NetChannel(const char *host, const char* service);

    bool send_message(NetMessage& msg);
    NetMessage* read_message();

    const bool is_open() const;
    void dissconect();

    friend class SocketConnectionLost;
};
#endif
