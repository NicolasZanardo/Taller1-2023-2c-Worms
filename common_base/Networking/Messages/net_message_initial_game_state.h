#ifndef COMMON_NET_MESSAGE_INITIAL_GAME_SATE_H_
#define COMMON_NET_MESSAGE_INITIAL_GAME_SATE_H_

#include <vector>
#include "../../Game/beamDto.h"
#include "../../Game/wormDto.h"
#include "net_message_dependencies.h"

class NetMessageInitialGameState : public NetMessage {
public:
    float room_width;
    float room_height;
    float water_height_level;
    std::vector<BeamDto> beams;
    std::vector<WormDto> worms;
    std::vector<int> client_ids_turn_order;
    
    NetMessageInitialGameState();
    NetMessageInitialGameState(float room_width, float room_height, float water_height_level);
    ~NetMessageInitialGameState() override {};

    void add(const BeamDto& beam);
    void add(const WormDto& worm);

    void add(const int turn);

    void push_data_into(NetBuffer& container) override;
    void pull_data_from(NetProtocolInterpreter& channel) override;
    void execute(NetMessageBehaviour& interpreter) override;
};
#endif
