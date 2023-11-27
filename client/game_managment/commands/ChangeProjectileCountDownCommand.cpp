#include "ChangeProjectileCountDownCommand.h"
#include "Networking/Messages/net_message_player_changed_projectile_countdown.h"

ChangeProjectileCountDownCommand::ChangeProjectileCountDownCommand(ProjectileCountDown countdown): countdown(countdown) {}

std::shared_ptr<NetMessage> ChangeProjectileCountDownCommand::create_net_message(int client_id) const {
    return std::make_shared<NetMessagePlayerChangedProjectileCountdown>(client_id, countdown);
}
