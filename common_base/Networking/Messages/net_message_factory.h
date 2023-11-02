#ifndef COMMON_NET_MESSAGE_FACTORY_H_
#define COMMON_NET_MESSAGE_FACTORY_H_

#include "net_message.h"
#include "net_message_test.h"

class NetMessageFactory {
    public:
    static NetMessage* recieve(Socket& channel) {
        NetProtocolInterpreter interpreter(channel);
        uint16_t type = interpreter.read_byte();
        
        NetMessage* inst;
        switch (type) {
            case NET_MESSAGE_TYPE_TEST:
                inst = new NetMessage_test();
                break;
            default:
                break;
        }

        inst->pull_data_from(interpreter);
        return inst;
    }
};
#endif
