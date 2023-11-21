#ifndef TP_WORMS_NETMESSAGEUSERSHOOT_H
#define TP_WORMS_NETMESSAGEUSERSHOOT_H

#include "net_message_dependencies.h"
#include "../../Game/WeaponDto.h"

class NetMessagePlayerShot : public NetMessage {
public:
    int client_id;
    WeaponDto weapon;
    float angle;
    float power;

    NetMessagePlayerShot();

    NetMessagePlayerShot(int client_id, WeaponDto weapon, float angle, float power);

    virtual void push_data_into(NetBuffer &container) override;
    virtual void pull_data_from(NetProtocolInterpreter &channel) override;
    virtual void execute(NetMessageBehaviour &interpreter) override;
};

#endif
