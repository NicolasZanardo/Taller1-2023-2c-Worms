#ifndef TP_WORMS_NET_MESSAGE_GAME_ENDED_H
#define TP_WORMS_NET_MESSAGE_GAME_ENDED_H

#include "net_message_dependencies.h"

class NetMessageGameEnded : public NetMessage {
public:
    int winner_client_id;

    NetMessageGameEnded();

    explicit NetMessageGameEnded(int client_id);

    void push_data_into(NetBuffer &container) override;

    void pull_data_from(NetProtocolInterpreter &channel) override;

    void execute(NetMessageBehaviour &interpreter) override;
};


#endif //TP_WORMS_NET_MESSAGE_GAME_ENDED_H
