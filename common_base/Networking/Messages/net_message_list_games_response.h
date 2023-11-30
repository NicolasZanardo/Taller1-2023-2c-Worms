#ifndef COMMON_NET_MESSAGE_LIST_GAMES_RESPONSE_H_
#define COMMON_NET_MESSAGE_LIST_GAMES_RESPONSE_H_

#include <list>
#include <string>

#include "../../Game/game_info_dto.h"
#include "net_message_dependencies.h"

class NetMessageListGamesResponse : public NetMessage {
public:
    NetMessageListGamesResponse();
    virtual ~NetMessageListGamesResponse() = default;

    void push_data_into(NetBuffer& container) override;
    void pull_data_from(NetProtocolInterpreter& channel) override;
    void execute(NetMessageBehaviour& interpreter) override;

    std::list<GameInfoDTO> games_info;
};

#endif  // COMMON_NET_MESSAGE_LIST_GAMES_RESPONSE_H_
