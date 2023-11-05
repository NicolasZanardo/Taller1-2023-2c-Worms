#include "net_message_factory.h"

#include "net_message_test.h"
#include "net_message_chat.h"
#include "net_message_leave.h"

NetMessage* NetMessageFactory::recieve(Socket& channel) {
    NetProtocolInterpreter interpreter(channel);
    uint16_t type = interpreter.read_byte();
    
    NetMessage* inst;
    switch (type) {
        case NET_MESSAGE_TYPE_TEST:
            inst = new NetMessage_test();
            break;
        case NET_MESSAGE_TYPE_CHAT:
            inst = new NetMessageChat();
            break;
        case NET_MESSAGE_TYPE_LEAVE:
            inst = new NetMessageLeave();
            break;
        default:
            break;
    }

    inst->pull_data_from(interpreter);
    return inst;
}
