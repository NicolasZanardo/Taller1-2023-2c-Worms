#ifndef COMMON_NET_MESSAGE_JOIN_GAME_H_
#define COMMON_NET_MESSAGE_JOIN_GAME_H_

#include <string>

#include "net_message_dependencies.h"

class NetMessageJoinGame : public NetMessage {
public:
    NetMessageJoinGame();
    NetMessageJoinGame(const std::string& game_room);
    virtual ~NetMessageJoinGame() = default;

    void push_data_into(NetBuffer& container) override;
    void pull_data_from(NetProtocolInterpreter& channel) override;
    void execute(NetMessageBehaviour& interpreter) override;

    std::string game_room;
};

#endif  // COMMON_NET_MESSAGE_JOIN_GAME_H_
