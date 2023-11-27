#include <iostream>
#include "net_message_player_changed_projectile_countdown.h"

NetMessagePlayerChangedProjectileCountdown::NetMessagePlayerChangedProjectileCountdown()
    : NetMessage(NET_MESSAGE_TYPE_PLAYER_CHANGED_PROJECTILE_COUNTDOWN)
{}

NetMessagePlayerChangedProjectileCountdown::NetMessagePlayerChangedProjectileCountdown(int client_id, ProjectileCountDown count_down)
    : NetMessage(NET_MESSAGE_TYPE_PLAYER_CHANGED_PROJECTILE_COUNTDOWN),
      client_id(client_id), count_down(count_down)
{}

void NetMessagePlayerChangedProjectileCountdown::push_data_into(NetBuffer& container) {
    NetMessage::push_data_into(container);
    container.push_int(client_id);
    container.push_int(static_cast<int>(count_down));
}

void NetMessagePlayerChangedProjectileCountdown::pull_data_from(NetProtocolInterpreter& channel) {
    client_id = channel.read_int();
    count_down = static_cast<ProjectileCountDown>(channel.read_int());
}

void NetMessagePlayerChangedProjectileCountdown::execute(NetMessageBehaviour& interpreter) {
    interpreter.run(this);
}