#include "net_message_initial_game_state.h"

NetMessageInitialGameState::NetMessageInitialGameState()
    : NetMessage(NET_MESSAGE_TYPE_INITIAL_STATE)
    {}

NetMessageInitialGameState::NetMessageInitialGameState(float room_width, float room_height)
        : NetMessage(NET_MESSAGE_TYPE_INITIAL_STATE),
        room_width(room_width),
        room_height(room_height),
        beams()
{}

void NetMessageInitialGameState::push_data_into(NetBuffer& container) {
    NetMessage::push_data_into(container);
    container.push_float(room_width);
    container.push_float(room_height);
    container.push_short(beams.size());
    for(auto it : beams) {
        container.push_float(it.x);
        container.push_float(it.y);
        container.push_float(it.angle);
        container.push_byte(static_cast<uint8_t>(it.type));
    }
}

void NetMessageInitialGameState::pull_data_from(NetProtocolInterpreter& channel) {
    room_width = channel.read_float();
    room_height = channel.read_float();
    short size = channel.read_short();
    for(short i = 0; i < size; i++) {
        beams.emplace_back(
            channel.read_float(),
            channel.read_float(),
            channel.read_float(),
            static_cast<BeamDto::Type>(channel.read_byte())
        );
    }
}

void NetMessageInitialGameState::add(const BeamDto& beam) {
    beams.emplace_back(beam.x, beam.y, beam.angle, beam.type);
}

void NetMessageInitialGameState::execute(NetMessageBehaviour& interpreter) {
    interpreter.run(this);
}
