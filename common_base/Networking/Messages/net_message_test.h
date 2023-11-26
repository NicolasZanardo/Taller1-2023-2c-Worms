#ifndef COMMON_NET_MESSAGE_TEST_H_
#define COMMON_NET_MESSAGE_TEST_H_

#include "net_message_dependencies.h"

class NetMessage_test : public NetMessage {
    void push_data_into(NetBuffer& container) override {
        NetMessage::push_data_into(container);
        container.push_short(test_short);
        container.push_int(test_uint);
        container.push_float(test_float);
        container.push_string(test_string);
    }

    void pull_data_from(NetProtocolInterpreter& channel) override {
        test_short = channel.read_short();
        test_uint = channel.read_int();
        test_float = channel.read_float();
        test_string = channel.read_string();
    }

    void execute(NetMessageBehaviour& interpreter) override {
        interpreter.run(this);
    }

    public:
    uint16_t test_short;
    uint32_t test_uint;
    std::string test_string;
    float test_float;
    
    NetMessage_test() :
        NetMessage(NET_MESSAGE_TYPE_TEST)
    {}
};
#endif
