#ifndef COMMON_NET_MESSAGE_CREATE_GAME_RESPONSE_H_
#define COMMON_NET_MESSAGE_CREATE_GAME_RESPONSE_H_

#include <string>

#include "net_message_dependencies.h"

class NetMessageCreateGameResponse : public NetMessage {
public:
    NetMessageCreateGameResponse() = delete;
    NetMessageCreateGameResponse(bool was_created);
    virtual ~NetMessageCreateGameResponse() = default;

    void push_data_into(NetBuffer& container) override;
    void pull_data_from(NetProtocolInterpreter& channel) override;
    void execute(NetMessageBehaviour& interpreter) override;

    bool was_created;
};

#endif  // COMMON_NET_MESSAGE_CREATE_GAME_RESPONSE_H_
