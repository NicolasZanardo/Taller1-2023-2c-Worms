#include "net_message_game_state_update.h"

NetMessageGameStateUpdate::NetMessageGameStateUpdate()
    : NetMessage(NET_MESSAGE_TYPE_UPDATE_STATE) {}

NetMessageGameStateUpdate::NetMessageGameStateUpdate(
    int active_client_id,
    int active_entity_id,
    float wind_speed,
    float remaining_game_time,
    float remaining_turn_time
) : NetMessage(NET_MESSAGE_TYPE_UPDATE_STATE),
    current_turn_client_id(active_client_id),
    focused_entity_id(active_entity_id),
    wind_speed(wind_speed),
    remaining_game_time(remaining_game_time),
    remaining_turn_time(remaining_turn_time) {}

NetMessageGameStateUpdate::NetMessageGameStateUpdate(GameState state) :
    NetMessage(NET_MESSAGE_TYPE_UPDATE_STATE),
    current_turn_client_id(state.current_turn_client_id),
    current_turn_worm_id(state.current_turn_worm_id),
    focused_entity_id(state.focused_entity_id),
    wind_speed(state.wind_speed),
    remaining_game_time(state.remaining_game_time),
    remaining_turn_time(state.remaining_turn_time) {}


void NetMessageGameStateUpdate::add(const WormDto &worm) {
    worms.push_back(worm);
}

void NetMessageGameStateUpdate::add(const ProjectileDto &bullet) {
    projectiles.push_back(bullet);
}

void NetMessageGameStateUpdate::add(const WorldEventDto &event) {
    events.push_back(event);
}

void NetMessageGameStateUpdate::execute(NetMessageBehaviour &interpreter) {
    interpreter.run(this);
}

void NetMessageGameStateUpdate::push_data_into(NetBuffer &container) {
    NetMessage::push_data_into(container);
    container.push_int(current_turn_client_id);
    container.push_int(current_turn_worm_id);
    container.push_int(focused_entity_id);
    container.push_float(wind_speed);
    container.push_float(remaining_game_time);
    container.push_float(remaining_turn_time);

    container.push_short(worms.size());
    for (size_t i = 0; i < worms.size(); i++) {
        container.push_int(worms[i].client_id);
        container.push_int(worms[i].entity_id);
        container.push_float(worms[i].x);
        container.push_float(worms[i].y);
        container.push_float(worms[i].angle);
        container.push_bool(worms[i].is_facing_right);
        container.push_int(worms[i].life);
        container.push_byte(static_cast<uint8_t>(worms[i].movement_state));
        container.push_byte(static_cast<uint8_t>(worms[i].weapon_hold));
        container.push_float(worms[i].aiming_angle);
    }

    container.push_short(projectiles.size());
    for (size_t i = 0; i < projectiles.size(); i++) {
        container.push_int(projectiles[i].entity_id);
        container.push_byte(static_cast<uint8_t>(projectiles[i].type));
        container.push_float(projectiles[i].x);
        container.push_float(projectiles[i].y);
    }

    container.push_short(events.size());
    for (size_t i = 0; i < events.size(); i++) {
        container.push_int(events[i].entity_id);
        container.push_float(events[i].x);
        container.push_float(events[i].y);
        container.push_byte(static_cast<uint8_t>(events[i].type));
    }
}

void NetMessageGameStateUpdate::pull_data_from(NetProtocolInterpreter &channel) {
    current_turn_client_id = channel.read_int();
    current_turn_worm_id = channel.read_int();
    focused_entity_id = channel.read_int();
    wind_speed = channel.read_float();
    remaining_game_time = channel.read_float();
    remaining_turn_time = channel.read_float();

    short worms_size = channel.read_short();
    for (int i = 0; i < worms_size; i++) {
        auto client_id = channel.read_int();
        auto entity_id = channel.read_int();
        auto x = channel.read_float();
        auto y = channel.read_float();
        auto angle = channel.read_float();
        auto is_facing_right = channel.read_bool();
        auto life = channel.read_int();
        auto state = static_cast<MovementStateDto>(channel.read_byte());
        auto weapon_hold = static_cast<WeaponTypeDto>(channel.read_byte());
        auto aiming_angle = channel.read_float();

        worms.emplace_back(client_id, entity_id, x, y, angle, is_facing_right, life, state, weapon_hold, aiming_angle);
    }

    short bullets_size = channel.read_short();
    for (int i = 0; i < bullets_size; i++) {
        auto entity_id = channel.read_int();
        auto type = static_cast<ProjectileTypeDto>(channel.read_byte());
        auto x = channel.read_float();
        auto y = channel.read_float();

        projectiles.emplace_back(entity_id, type, x, y);
    }

    short events_size = channel.read_short();
    for (int i = 0; i < events_size; i++) {
        auto entity_id = channel.read_int();
        auto x = channel.read_float();
        auto y = channel.read_float();
        auto type = static_cast<WorldEventDto::Type>(channel.read_byte());

        events.emplace_back(entity_id, x, y, type);
    }
}
