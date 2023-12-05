#include "net_message_player_toggle_cheat.h"

NetMessagePlayerToggleCheat::NetMessagePlayerToggleCheat()
    : NetMessage(NET_MESSAGE_TYPE_PLAYER_TOGGLE_CHEAT)
{}

NetMessagePlayerToggleCheat::NetMessagePlayerToggleCheat(int client_id, CheatType cheat)
    : NetMessage(NET_MESSAGE_TYPE_PLAYER_TOGGLE_CHEAT),
      client_id(client_id), cheat(cheat)
{}

void NetMessagePlayerToggleCheat::push_data_into(NetBuffer& container) {
    NetMessage::push_data_into(container);
    container.push_int(client_id);
    container.push_byte(static_cast<uint8_t>(cheat));
}

void NetMessagePlayerToggleCheat::pull_data_from(NetProtocolInterpreter& channel) {
    client_id = channel.read_int();
    cheat = static_cast<CheatType>(channel.read_byte());
}

void NetMessagePlayerToggleCheat::execute(NetMessageBehaviour& interpreter) {
    interpreter.run(this);
}