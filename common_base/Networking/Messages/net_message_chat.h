#ifndef COMMON_NET_MESSAGE_CHAT_H_
#define COMMON_NET_MESSAGE_CHAT_H_

#include <string>
#include <cstdint>
#include "../../socket.h"
#include "../net_buffer.h"
#include "../net_protocol_interpreter.h"
#include "net_message_behaviour.h"
#include "net_message.h"

class NetMessageChat : public NetMessage {
    public:
    int client_id;
    std::string chat;
    NetMessageChat();
    NetMessageChat(const int client_id, const std::string chat);

    virtual void push_data_into(NetBuffer& container) override;
    virtual void pull_data_from(NetProtocolInterpreter& channel) override;
    virtual void execute(NetMessageBehaviour& interpreter) override;
};
#endif
