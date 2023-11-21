#include "net_message_player_shot.h"

NetMessagePlayerShot::NetMessagePlayerShot()
        : NetMessage(NET_MESSAGE_TYPE_PLAYER_SHOT)
{}

NetMessagePlayerShot::NetMessagePlayerShot(int client_id, WeaponDto weapon, float angle, float power)
        : NetMessage(NET_MESSAGE_TYPE_PLAYER_SHOT),
          client_id(client_id),  weapon(weapon), angle(angle), power(power)
{}

void NetMessagePlayerShot::push_data_into(NetBuffer& container) {
    NetMessage::push_data_into(container);
    container.push_uint(client_id);
    container.push_byte(static_cast<uint8_t>(weapon));
    container.push_float(angle);
    container.push_float(power);

}

void NetMessagePlayerShot::pull_data_from(NetProtocolInterpreter& channel) {
    client_id = channel.read_uint();
    weapon = static_cast<WeaponDto>(channel.read_byte());
    angle = channel.read_float();
    power = channel.read_float();
}

void NetMessagePlayerShot::execute(NetMessageBehaviour& interpreter) {
    interpreter.run(this);
}