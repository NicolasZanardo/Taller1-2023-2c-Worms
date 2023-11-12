#ifndef COMMON_NET_MESSAGE_INITIAL_GAME_SATE_H_
#define COMMON_NET_MESSAGE_INITIAL_GAME_SATE_H_

#include <vector>
#include "../../Game/beamDto.h"
#include "net_message_dependencies.h"

struct NetMessageInitialGameState : public NetMessage {
    float room_width;
    float room_height;
    std::vector<BeamDto> beams;
    
    NetMessageInitialGameState();
    NetMessageInitialGameState(float room_width, float room_height);
    ~NetMessageInitialGameState() override {};

    void add(const BeamDto& beam);

    virtual void push_data_into(NetBuffer& container) override;
    virtual void pull_data_from(NetProtocolInterpreter& channel) override;
    virtual void execute(NetMessageBehaviour& interpreter) override;
};
#endif
