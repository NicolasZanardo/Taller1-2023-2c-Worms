#ifndef TP_WORMS_NET_MESSAGE_PLAYER_CHANGED_WEAPON_H
#define TP_WORMS_NET_MESSAGE_PLAYER_CHANGED_WEAPON_H

#include "net_message_dependencies.h"
#include "../../Game/WeaponTypeDto.h"

class NetMessagePlayerChangedWeapon : public NetMessage {
public:
    uint32_t client_id;
    WeaponTypeDto chosen_weapon;

    NetMessagePlayerChangedWeapon();

    NetMessagePlayerChangedWeapon(size_t client_id, WeaponTypeDto chosen_weapon);

    void push_data_into(NetBuffer &container) override;

    void pull_data_from(NetProtocolInterpreter &channel) override;

    void execute(NetMessageBehaviour &interpreter) override;

};

#endif
