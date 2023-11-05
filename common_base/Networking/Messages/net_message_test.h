#ifndef COMMON_NET_MESSAGE_TEST_H_
#define COMMON_NET_MESSAGE_TEST_H_

#include <cstdint>
#include "../../socket.h"
#include "../net_buffer.h"
#include "../net_protocol_interpreter.h"
#include "net_message_behaviour.h"
#include "net_message.h"

class NetMessage_test : public NetMessage {
    void push_data_into(NetBuffer& container) override {
        NetMessage::push_data_into(container);
        container.push_short(test_short);
        container.push_uint(test_uint);
        container.push_string(test_string);
    }

    void pull_data_from(NetProtocolInterpreter& channel) override {
        test_short = channel.read_short();
        test_uint = channel.read_uint();
        test_string = channel.read_string();
    }

    void execute(NetMessageBehaviour& interpreter) override {
        interpreter.run(this);
    }

    public:
    uint16_t test_short;
    uint32_t test_uint;
    std::string test_string;
    
    NetMessage_test() :
        NetMessage(NET_MESSAGE_TYPE_TEST),
        test_short(250),
        test_uint(313131),
        test_string("Test string")
    {}
};
#endif
