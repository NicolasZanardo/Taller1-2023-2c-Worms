#ifndef SERVER_NET_MESSAGE_GAME_ACTION_H
#define SERVER_NET_MESSAGE_GAME_ACTION_H

#include "net_message_dependencies.h"
#include "../../Game/ActionTypeDto.h"

class NetMessageGameAction: public NetMessage{
public:
    uint32_t client_id{};
    ActionTypeDto action;

    NetMessageGameAction();
    NetMessageGameAction(size_t client_id, ActionTypeDto action);

    virtual void push_data_into(NetBuffer& container) override;
    virtual void pull_data_from(NetProtocolInterpreter& channel) override;
    virtual void execute(NetMessageBehaviour& interpreter) override;
};


#endif
