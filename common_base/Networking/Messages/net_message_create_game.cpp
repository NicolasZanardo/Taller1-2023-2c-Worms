#include "net_message_create_game.h"

NetMessageCreateGame::NetMessageCreateGame()
    : NetMessage(NET_MESSAGE_TYPE_CREATE_GAME) {}

NetMessageCreateGame::NetMessageCreateGame(const std::string& game_room, const std::string& scenario, uint8_t num_players)
    : NetMessage(NET_MESSAGE_TYPE_CREATE_GAME)
    , game_room(game_room)
    , num_players(num_players) {}

void NetMessageCreateGame::push_data_into(NetBuffer& container) {
    NetMessage::push_data_into(container);
    container.push_string(this->game_room);
    container.push_string(this->scenario);
    container.push_byte(this->num_players);
}

void NetMessageCreateGame::pull_data_from(NetProtocolInterpreter& channel) {
    this->game_room = channel.read_string();
    this->scenario = channel.read_string();
    this->num_players = channel.read_byte();
}

void NetMessageCreateGame::execute(NetMessageBehaviour& interpreter) {
    interpreter.run(this);
}
