#ifndef TP_WORMS_NET_MESSAGE_PLAYER_CHANGED_PROJECTILE_COUNTDOWN_H
#define TP_WORMS_NET_MESSAGE_PLAYER_CHANGED_PROJECTILE_COUNTDOWN_H

#include <cstdio>
#include "net_message_dependencies.h"
#include "../../Game/ProjectileCountDown.h"

class NetMessagePlayerChangedProjectileCountdown : public NetMessage {
public:
    int client_id;
    ProjectileCountDown count_down;

    NetMessagePlayerChangedProjectileCountdown();

    NetMessagePlayerChangedProjectileCountdown(int client_id, ProjectileCountDown count_down);

    void push_data_into(NetBuffer &container) override;

    void pull_data_from(NetProtocolInterpreter &channel) override;

    void execute(NetMessageBehaviour &interpreter) override;

};


#endif //TP_WORMS_NET_MESSAGE_PLAYER_CHANGED_PROJECTILE_COUNTDOWN_H
