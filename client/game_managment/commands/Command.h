#ifndef TP_WORMS_COMMAND_H
#define TP_WORMS_COMMAND_H

#include <memory>
#include "Networking/Messages/net_message.h"

class Command {
public:
    Command() = default;

    Command(const Command&) = delete;
    Command& operator=(const Command&) = delete;
    Command(Command&& other) = delete;
    Command& operator=(Command&& other) = delete;

    virtual std::shared_ptr<NetMessage> create_net_message(int clientId) const = 0;
    virtual ~Command() {}
};


#endif //TP_WORMS_COMMAND_H
