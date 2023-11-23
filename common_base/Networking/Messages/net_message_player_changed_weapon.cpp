#include "net_message_player_changed_weapon.h"

NetMessagePlayerChangedWeapon::NetMessagePlayerChangedWeapon()
        : NetMessage(NET_MESSAGE_TYPE_PLAYER_CHANGED_WEAPON)
{}

NetMessagePlayerChangedWeapon::NetMessagePlayerChangedWeapon(size_t client_id, WeaponTypeDto chosen_weapon)
        : NetMessage(NET_MESSAGE_TYPE_PLAYER_CHANGED_WEAPON),
          client_id(client_id), chosen_weapon(chosen_weapon)
{}

void NetMessagePlayerChangedWeapon::push_data_into(NetBuffer& container) {
    NetMessage::push_data_into(container);
    container.push_uint(client_id);
    container.push_byte(static_cast<uint8_t>(chosen_weapon));
}

void NetMessagePlayerChangedWeapon::pull_data_from(NetProtocolInterpreter& channel) {
    client_id = channel.read_uint();
    chosen_weapon = static_cast<WeaponTypeDto>(channel.read_byte());
}

void NetMessagePlayerChangedWeapon::execute(NetMessageBehaviour& interpreter) {
    interpreter.run(this);
}