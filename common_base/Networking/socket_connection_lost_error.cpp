#include "socket_connection_lost_error.h"

SocketConnectionLost::SocketConnectionLost(const Socket* who) noexcept :
    instance(who)
    {}
SocketConnectionLost::~SocketConnectionLost() {}

const char* SocketConnectionLost::what() const noexcept {
    return "Connection with client lost";
}

const bool SocketConnectionLost::was(const Socket* inst) const noexcept {
    return instance == inst;
}

const bool SocketConnectionLost::was(const NetChannel* inst) const noexcept {
    return instance == &inst->socket;
}