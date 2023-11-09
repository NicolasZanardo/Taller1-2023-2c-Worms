#include "net_message_game_state_update.h"

NetMessageGameStateUpdate::NetMessageGameStateUpdate()
    : NetMessage(NET_MESSAGE_TYPE_UPDATE_STATE)
    {}

NetMessageGameStateUpdate::NetMessageGameStateUpdate(
        int id_active_entity,
        float wind_speed,
        float remaining_game_time,
        float remaining_turn_time
    ) : NetMessage(NET_MESSAGE_TYPE_UPDATE_STATE),
    id_active_entity(id_active_entity),
    wind_speed(wind_speed),
    remaining_game_time(remaining_game_time),
    remaining_turn_time(remaining_turn_time)
    {}

void add(Worm& worm);
void add(Bullet& bullet);
void add(WorldEvent& event);

//virtual void execute(NetMessageBehaviour& interpreter) override;

void NetMessageGameStateUpdate::push_data_into(NetBuffer& container) {
    NetMessage::push_data_into(container);
    container.push_uint(id_active_entity);
    container.push_float(wind_speed);
    container.push_float(remaining_game_time);
    container.push_float(remaining_turn_time);

    container.push_short(worms.size());
    for(int i = 0; i < worms.size(); i++) {
        container.push_uint(worms[i].client_id);
        container.push_uint(worms[i].entity_id);
        container.push_float(worms[i].x);
        container.push_float(worms[i].y);
        container.push_uint(worms[i].life);
        container.push_byte(static_cast<uint8_t>(worms[i].state));
    }

    container.push_short(bullets.size());
    for(int i = 0; i < bullets.size(); i++) {
        container.push_uint(bullets[i].entity_id);
        container.push_float(bullets[i].x);
        container.push_float(bullets[i].y);
        container.push_float(bullets[i].angle);
        container.push_byte(static_cast<uint8_t>(bullets[i].type));
    }

    container.push_short(events.size());
    for(int i = 0; i < events.size(); i++) {
        container.push_uint(events[i].entity_id);
        container.push_float(events[i].x);
        container.push_float(events[i].y);
        container.push_byte(static_cast<uint8_t>(events[i].type));
    }
}

void NetMessageGameStateUpdate::pull_data_from(NetProtocolInterpreter& channel) {
    id_active_entity = channel.read_uint();
    wind_speed = channel.read_float();
    remaining_game_time = channel.read_float();
    remaining_turn_time = channel.read_float();

    short worms_size = channel.read_short();
    for(int i = 0; i < worms_size; i++) {
        worms.emplace_back (
            channel.read_uint(),
            channel.read_uint(),
            channel.read_float(),
            channel.read_float(),
            channel.read_uint(),
            static_cast<Worm::State>(channel.read_byte())
        );
    }

    short bullets_size = channel.read_short();
    for(int i = 0; i < bullets_size; i++) {
        bullets.emplace_back(
            channel.read_uint(),
            channel.read_float(),
            channel.read_float(),
            channel.read_float(),
            static_cast<Bullet::Type>(channel.read_byte())
        );
    }

    short events_size = channel.read_short();
    for(int i = 0; i < events_size; i++) {
        events.emplace_back(
            channel.read_uint(),
            channel.read_float(),
            channel.read_float(),
            static_cast<WorldEvent::Type>(channel.read_byte())
        );
    }
}

void NetMessageGameStateUpdate::execute(NetMessageBehaviour& interpreter) {
    interpreter.run(this);
}
