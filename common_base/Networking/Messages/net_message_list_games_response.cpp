#include "net_message_list_games_response.h"

NetMessageListGamesResponse::NetMessageListGamesResponse()
    : NetMessage(NET_MESSAGE_TYPE_LIST_GAMES_RESPONSE) {}

NetMessageListGamesResponse::NetMessageListGamesResponse(std::list<GameInfoDTO> games_info)
    : NetMessage(NET_MESSAGE_TYPE_LIST_GAMES_RESPONSE)
    , games_info(std::move(games_info)){}

void NetMessageListGamesResponse::push_data_into(NetBuffer& container) {
    NetMessage::push_data_into(container);

    container.push_int(static_cast<uint32_t>(this->games_info.size()));

    for (auto& game : this->games_info) {
        container.push_string(game.name);
        container.push_string(game.scenario);
        container.push_byte(game.total_players);
        container.push_byte(game.joined_players);
    }
}

void NetMessageListGamesResponse::pull_data_from(NetProtocolInterpreter& channel) {
    uint32_t size = channel.read_int();

    for (uint32_t i = 0; i < size; i++) {
        std::string name = channel.read_string();
        std::string scenario = channel.read_string();
        uint8_t total_players = channel.read_byte();
        uint8_t joined_players = channel.read_byte();

        GameInfoDTO dto(GameInfoDTO(std::move(name), std::move(scenario), total_players, joined_players));

        // this->games_info.push_back(std::move(dto));
    }
}

void NetMessageListGamesResponse::execute(NetMessageBehaviour& interpreter) {
    interpreter.run(this);
}
