#ifndef COMMON_NET_MESSAGE_CREATE_GAME_H_
#define COMMON_NET_MESSAGE_CREATE_GAME_H_

#include <string>

#include "net_message_dependencies.h"

class NetMessageCreateGame : public NetMessage {
public:
    NetMessage() = delete;
    NetMessageCreateGame(const std::string& game_room, uint8_t num_players);
    virtual ~NetMessageCreateGame() = default;

    void push_data_into(NetBuffer& container) override;
    void pull_data_from(NetProtocolInterpreter& channel) override;
    void execute(NetMessageBehaviour& interpreter) override;

    std::string game_room;
    uint8_t num_players;
};

#endif  // COMMON_NET_MESSAGE_CREATE_GAME_H_
