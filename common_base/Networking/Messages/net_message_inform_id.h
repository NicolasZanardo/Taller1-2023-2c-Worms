#ifndef COMMON_NET_MESSAGE_INFORM_ID_H_
#define COMMON_NET_MESSAGE_INFORM_ID_H_

#include <string>
#include "net_message_dependencies.h"

class NetMessageInformID : public NetMessage {
    public:
    int client_id;
    NetMessageInformID();
    explicit NetMessageInformID(const int client_id);

    virtual void push_data_into(NetBuffer& container) override;
    virtual void pull_data_from(NetProtocolInterpreter& channel) override;
    virtual void execute(NetMessageBehaviour& interpreter) override;
};
#endif
