#ifndef COMMON_NET_MESSAGE_CREATE_GAME_H_
#define COMMON_NET_MESSAGE_CREATE_GAME_H_

#include <string>

#include "net_message_dependencies.h"

class NetMessageCreateGame : public NetMessage {
public:
    NetMessageCreateGame();
    NetMessageCreateGame(const std::string& game_room, const std::string& scenario, uint8_t num_players);
    virtual ~NetMessageCreateGame() = default;

    virtual void push_data_into(NetBuffer& container) override;
    virtual void pull_data_from(NetProtocolInterpreter& channel) override;
    virtual void execute(NetMessageBehaviour& interpreter) override;

    std::string game_room;
    std::string scenario;
    uint8_t num_players;
};

#endif  // COMMON_NET_MESSAGE_CREATE_GAME_H_
