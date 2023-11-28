#ifndef COMMON_NET_MESSAGE_JOIN_GAME_RESPONSE_H_
#define COMMON_NET_MESSAGE_JOIN_GAME_RESPONSE_H_

#include <string>

#include "net_message_dependencies.h"

class NetMessageJoinGameResponse : public NetMessage {
public:
    NetMessageJoinGameResponse() = delete;
    NetMessageJoinGameResponse(bool was_Joind);
    virtual ~NetMessageJoinGameResponse() = default;

    void push_data_into(NetBuffer& container) override;
    void pull_data_from(NetProtocolInterpreter& channel) override;
    void execute(NetMessageBehaviour& interpreter) override;

    bool was_joined;
};

#endif  // COMMON_NET_MESSAGE_JOIN_GAME_RESPONSE_H_
