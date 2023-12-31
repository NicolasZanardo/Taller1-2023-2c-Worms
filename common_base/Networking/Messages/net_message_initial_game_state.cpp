#include "net_message_initial_game_state.h"
#include <iostream>

NetMessageInitialGameState::NetMessageInitialGameState()
    : NetMessage(NET_MESSAGE_TYPE_INITIAL_STATE) {}

NetMessageInitialGameState::NetMessageInitialGameState(float room_width, float room_height, float water_height_level)
    : NetMessage(NET_MESSAGE_TYPE_INITIAL_STATE),
      room_width(room_width),
      room_height(room_height),
      water_height_level(water_height_level),
      beams(),
      worms() {}

void NetMessageInitialGameState::push_data_into(NetBuffer &container) {
    NetMessage::push_data_into(container);
    container.push_float(room_width);
    container.push_float(room_height);
    container.push_float(water_height_level);

    container.push_short(beams.size());
    for (auto &it: beams) {
        container.push_float(it.x);
        container.push_float(it.y);
        container.push_float(it.angle);
        container.push_byte(static_cast<uint8_t>(it.type));
    }

    container.push_short(worms.size());
    for(auto& it : worms) {
        container.push_int(it.client_id);
        container.push_int(it.entity_id);
        container.push_float(it.x);
        container.push_float(it.y);
        container.push_float(it.angle);
        container.push_bool(it.is_facing_right);
        container.push_int(it.life);
        container.push_byte(static_cast<uint8_t>(it.movement_state));
        container.push_byte(static_cast<uint8_t>(it.weapon_hold));
        container.push_float(it.aiming_angle);
    }

    container.push_short(client_ids_turn_order.size());
    for (auto& it : client_ids_turn_order) {
        container.push_int(it);
    }
}

void NetMessageInitialGameState::pull_data_from(NetProtocolInterpreter &channel) {
    room_width = channel.read_float();
    room_height = channel.read_float();
    water_height_level = channel.read_float();

    short beam_size = channel.read_short();
    for (short i = 0; i < beam_size; i++) {
        auto x = channel.read_float();
        auto y = channel.read_float();
        auto angle = channel.read_float();
        auto type = static_cast<BeamDto::Type>(channel.read_byte());

        beams.emplace_back(x, y, angle, type);
    }

    short worms_size = channel.read_short();
    for(int i = 0; i < worms_size; i++) {
        auto client_id = channel.read_int();
        auto entity_id = channel.read_int();
        auto x         = channel.read_float();
        auto y         = channel.read_float();
        auto angle     = channel.read_float();
        auto is_facing_right = channel.read_bool();
        auto life      = channel.read_int();
        auto state     = static_cast<WormStateDto>(channel.read_byte());
        auto weapon_hold     = static_cast<WeaponTypeDto>(channel.read_byte());
        auto aiming_angle     = channel.read_float();

        worms.emplace_back(client_id, entity_id, x, y, angle, is_facing_right, life, state, weapon_hold, aiming_angle);
    }

    short clients_amount = channel.read_short();
    for(int i = 0; i < clients_amount; i++) {
        client_ids_turn_order.emplace_back(channel.read_int());
    }
}

void NetMessageInitialGameState::add(const BeamDto &beam) {
    beams.emplace_back(beam.x, beam.y, beam.angle, beam.type);
}

void NetMessageInitialGameState::add(const WormDto &worm) {
    worms.push_back(worm);
}
void NetMessageInitialGameState::add(const int client_turn) {
    client_ids_turn_order.push_back(client_turn);
}

void NetMessageInitialGameState::execute(NetMessageBehaviour &interpreter) {
    interpreter.run(this);
}
