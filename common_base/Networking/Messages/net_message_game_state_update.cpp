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
    active_client_id(active_client_id),
    active_entity_id(active_entity_id),
    wind_speed(wind_speed),
    remaining_game_time(remaining_game_time),
    remaining_turn_time(remaining_turn_time) {}

void NetMessageGameStateUpdate::add(const WormDto &worm) {
    worms.push_back(worm);
}

void NetMessageGameStateUpdate::add(const BulletDto &bullet) {
    bullets.push_back(bullet);
}

void NetMessageGameStateUpdate::add(const WorldEventDto &event) {
    events.push_back(event);
}

void NetMessageGameStateUpdate::execute(NetMessageBehaviour &interpreter) {
    interpreter.run(this);
}

void NetMessageGameStateUpdate::push_data_into(NetBuffer &container) {
    NetMessage::push_data_into(container);
    container.push_uint(active_client_id);
    container.push_uint(active_entity_id);
    container.push_float(wind_speed);
    container.push_float(remaining_game_time);
    container.push_float(remaining_turn_time);

    container.push_short(worms.size());
    for (size_t i = 0; i < worms.size(); i++) {
        container.push_uint(worms[i].client_id);
        container.push_uint(worms[i].entity_id);
        container.push_float(worms[i].x);
        container.push_float(worms[i].y);
        container.push_uint(worms[i].life);
        container.push_byte(static_cast<uint8_t>(worms[i].state));
    }

    container.push_short(bullets.size());
    for (size_t i = 0; i < bullets.size(); i++) {
        container.push_uint(bullets[i].entity_id);
        container.push_float(bullets[i].x);
        container.push_float(bullets[i].y);
        container.push_float(bullets[i].angle);
        container.push_byte(static_cast<uint8_t>(bullets[i].type));
    }

    container.push_short(events.size());
    for (size_t i = 0; i < events.size(); i++) {
        container.push_uint(events[i].entity_id);
        container.push_float(events[i].x);
        container.push_float(events[i].y);
        container.push_byte(static_cast<uint8_t>(events[i].type));
    }
}

void NetMessageGameStateUpdate::pull_data_from(NetProtocolInterpreter &channel) {
    active_client_id = channel.read_uint();
    active_entity_id = channel.read_uint();
    wind_speed = channel.read_float();
    remaining_game_time = channel.read_float();
    remaining_turn_time = channel.read_float();

    short worms_size = channel.read_short();
    for (int i = 0; i < worms_size; i++) {
        worms.emplace_back(
                channel.read_uint(),
                channel.read_uint(),
                channel.read_float(),
                channel.read_float(),
                channel.read_uint(),
                static_cast<WormDto::State>(channel.read_byte())
        );
    }

    short bullets_size = channel.read_short();
    for (int i = 0; i < bullets_size; i++) {
        bullets.emplace_back(
                channel.read_uint(),
                channel.read_float(),
                channel.read_float(),
                channel.read_float(),
                static_cast<BulletDto::Type>(channel.read_byte())
        );
    }

    short events_size = channel.read_short();
    for (int i = 0; i < events_size; i++) {
        events.emplace_back(
                channel.read_uint(),
                channel.read_float(),
                channel.read_float(),
                static_cast<WorldEventDto::Type>(channel.read_byte())
        );
    }
}
