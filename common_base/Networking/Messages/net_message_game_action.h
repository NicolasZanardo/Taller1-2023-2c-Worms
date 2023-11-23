#ifndef SERVER_NET_MESSAGE_GAME_ACTION_H
#define SERVER_NET_MESSAGE_GAME_ACTION_H

#include "net_message_dependencies.h"
#include "../../Game/GameAction.h"

class NetMessageGameAction: public NetMessage{
public:
    uint32_t client_id{};
    GameAction action;

    NetMessageGameAction();
    NetMessageGameAction(size_t client_id, GameAction action);

    void push_data_into(NetBuffer& container) override;
    void pull_data_from(NetProtocolInterpreter& channel) override;
    void execute(NetMessageBehaviour& interpreter) override;
};


#endif
