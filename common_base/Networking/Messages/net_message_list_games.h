#ifndef COMMON_NET_MESSAGE_LIST_GAMES_H_
#define COMMON_NET_MESSAGE_LIST_GAMES_H_

#include <string>

#include "net_message_dependencies.h"

class NetMessageListGames : public NetMessage {
public:
    NetMessageListGames();
    virtual ~NetMessageListGames() = default;

    virtual void push_data_into(NetBuffer& container) override;
    virtual void pull_data_from(NetProtocolInterpreter& channel) override;
    virtual void execute(NetMessageBehaviour& interpreter) override;

    std::string game_room;
};

#endif  // COMMON_NET_MESSAGE_LIST_GAMES_H_
