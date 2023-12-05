#ifndef TP_WORMS_NET_MESSAGE_PLAYER_TOGGLE_CHEAT_H
#define TP_WORMS_NET_MESSAGE_PLAYER_TOGGLE_CHEAT_H


#include "net_message.h"
#include "Game/CheatType.h"

class NetMessagePlayerToggleCheat: public NetMessage {
public:
    int client_id;
    CheatType cheat;

    NetMessagePlayerToggleCheat();

    NetMessagePlayerToggleCheat(int client_id, CheatType cheat);

    void push_data_into(NetBuffer &container) override;

    void pull_data_from(NetProtocolInterpreter &channel) override;

    void execute(NetMessageBehaviour &interpreter) override;

};


#endif //TP_WORMS_NET_MESSAGE_PLAYER_TOGGLE_CHEAT_H
