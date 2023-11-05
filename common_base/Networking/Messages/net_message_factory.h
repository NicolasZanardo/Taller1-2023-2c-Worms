#ifndef COMMON_NET_MESSAGE_FACTORY_H_
#define COMMON_NET_MESSAGE_FACTORY_H_

#include "net_message.h"

class NetMessageFactory {
    public:
    static NetMessage* recieve(Socket& channel);
};
#endif
