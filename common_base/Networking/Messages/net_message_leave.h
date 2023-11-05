#ifndef COMMON_NET_MESSAGE_LEAVE_H_
#define COMMON_NET_MESSAGE_LEAVE_H_

#include <string>
#include "net_message_dependencies.h"

class NetMessageLeave : public NetMessage {
    public:
    int client_id;
    NetMessageLeave();
    explicit NetMessageLeave(const int client_id);

    virtual void push_data_into(NetBuffer& container) override;
    virtual void pull_data_from(NetProtocolInterpreter& channel) override;
    virtual void execute(NetMessageBehaviour& interpreter) override;
};
#endif
