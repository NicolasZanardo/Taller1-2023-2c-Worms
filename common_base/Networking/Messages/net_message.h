#ifndef COMMON_NET_MESSAGE_H_
#define COMMON_NET_MESSAGE_H_

#include <cstdint>
#include "../../socket.h"
#include "../net_buffer.h"
#include "../net_protocol_interpreter.h"
#include "net_message_behaviour.h"

#define NET_MESSAGE_TYPE_TEST 0
#define NET_MESSAGE_TYPE_CHAT 1
#define NET_MESSAGE_TYPE_LEAVE 2

class NetMessage {
    public:
    uint8_t msg_type;
    explicit NetMessage(uint8_t msg_type);

    // Tener en consideracion que el byte del tipo ya fue recibido
    virtual void pull_data_from(NetProtocolInterpreter& channel) = 0;
    virtual void push_data_into(NetBuffer& container);
    virtual void execute(NetMessageBehaviour& interpreter) = 0;

    virtual ~NetMessage() {}
};
#endif
