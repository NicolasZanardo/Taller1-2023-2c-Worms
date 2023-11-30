#ifndef COMMON_NET_MESSAGE_LIST_GAMES_H_
#define COMMON_NET_MESSAGE_LIST_GAMES_H_

#include <string>

#include "net_message_dependencies.h"

class NetMessageListGames : public NetMessage {
public:
    NetMessageListGames();
    virtual ~NetMessageListGames() = default;

    void push_data_into(NetBuffer& container) override;
    void pull_data_from(NetProtocolInterpreter& channel) override;
    void execute(NetMessageBehaviour& interpreter) override;

    std::string game_room;
};

#endif  // COMMON_NET_MESSAGE_LIST_GAMES_H_
