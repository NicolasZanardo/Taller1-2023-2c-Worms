#ifndef COMMON_NET_MESSAGE_GAME_SATE_UPDATE_H_
#define COMMON_NET_MESSAGE_GAME_SATE_UPDATE_H_

#include <vector>
#include "../../Game/wormDto.h"
#include "../../Game/eventDto.h"
#include "../../Game/ProjectileDto.h"
#include "net_message_dependencies.h"


class NetMessageGameStateUpdate : public NetMessage {
public:
    int current_turn_client_id;
    int current_turn_worm_id;
    int focused_entity_id;
    float wind_speed;
    float remaining_game_time;
    float remaining_turn_time;
    std::vector<WormDto> worms;
    std::vector<ProjectileDto> projectiles;
    std::vector<WorldEventDto> events;
    
    NetMessageGameStateUpdate();
    NetMessageGameStateUpdate(
        int active_client_id,
        int active_entity_id,
        int current_turn_worm_id,
        float wind_speed,
        float remaining_game_time,
        float remaining_turn_time
    );

    void add(const WormDto& worm);
    void add(const ProjectileDto& projectile);
    void add(const WorldEventDto& event);

    void push_data_into(NetBuffer& container) override;
    void pull_data_from(NetProtocolInterpreter& channel) override;
    void execute(NetMessageBehaviour& interpreter) override;
};
#endif
