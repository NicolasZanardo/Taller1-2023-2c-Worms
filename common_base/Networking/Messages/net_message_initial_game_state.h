#ifndef COMMON_NET_MESSAGE_INITIAL_GAME_SATE_H_
#define COMMON_NET_MESSAGE_INITIAL_GAME_SATE_H_

#include <vector>
#include "../../Game/beam.h"
#include "net_message_dependencies.h"

struct NetMessageInitialGameState : public NetMessage {
    float room_width;
    float room_height;
    std::vector<Beam> beams;
    
    NetMessageInitialGameState();

    void add(Beam& beam);

    virtual void push_data_into(NetBuffer& container) override;
    virtual void pull_data_from(NetProtocolInterpreter& channel) override;
    virtual void execute(NetMessageBehaviour& interpreter) override;
};
#endif
