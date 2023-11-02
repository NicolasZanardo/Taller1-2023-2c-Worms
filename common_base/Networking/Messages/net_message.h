#ifndef COMMON_NET_MESSAGE_H_
#define COMMON_NET_MESSAGE_H_

#include <cstdint>
#include "../../socket.h"
#include "../net_buffer.h"
#include "../net_protocol_interpreter.h"

#define NET_MESSAGE_TYPE_TEST 0

class NetMessage {
    protected:
    uint8_t msg_type;

    public:
    explicit NetMessage(uint8_t msg_type);

    virtual void push_data_into(NetBuffer& container);

    // Tener en consideracion que el byte del tipo ya fue recibido
    virtual void pull_data_from(NetProtocolInterpreter& channel) = 0;

    //static NetMessage* recieve(Socket& channel);

    virtual ~NetMessage() {}
};
#endif
