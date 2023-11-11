#ifndef COMMON_NET_MESSAGE_GAME_SATE_UPDATE_H_
#define COMMON_NET_MESSAGE_GAME_SATE_UPDATE_H_

#include <vector>
#include "../../Game/bulletDto.h"
#include "../../Game/wormDto.h"
#include "../../Game/eventDto.h"
#include "net_message_dependencies.h"


struct NetMessageGameStateUpdate : public NetMessage {
    int id_active_entity;
    float wind_speed; // positivo o negativo
    float remaining_game_time;
    float remaining_turn_time;
    std::vector<WormDto> worms;
    std::vector<BulletDto> bullets;
    std::vector<WorldEventDto> events;
    
    NetMessageGameStateUpdate();
    NetMessageGameStateUpdate(
        int id_active_entity,
        float wind_speed,
        float remaining_game_time,
        float remaining_turn_time
    );

    void add(const WormDto& worm);
    void add(const BulletDto& bullet);
    void add(const WorldEventDto& event);

    virtual void push_data_into(NetBuffer& container) override;
    virtual void pull_data_from(NetProtocolInterpreter& channel) override;
    virtual void execute(NetMessageBehaviour& interpreter) override;
};
#endif